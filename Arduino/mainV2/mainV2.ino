#include "SerialHandler.h"
// #include "CommandHandler.h"
#include "Stepper.h"
#include "elapsedMillis.h"

elapsedMillis debugPrintTime;
elapsedMillis HomingTime;

struct tableStatus stat; // structure for managing state of table 

struct stepCommand qdStepCommand; //qD stepcommand struct


class StepperHandler steppers; //initialize stepper handler
class SerialHandler ser; // intialize serial handler


long radialISRcalls = 0;
long angularISRcalls = 0;



// ISR for radial step movement
ISR(TIMER3_COMPA_vect){
  steppers.radialStepISR();
  radialISRcalls ++;
}

//ISR for angular step movement
ISR(TIMER1_COMPA_vect){
  steppers.angularStepISR();
  angularISRcalls++;
}

void stall(){
  steppers.stallISR();
  stat.isHomed = false;
  stat.isStalled = true;
}

//called after stall happens, back up from stall and sets position to zero

void home(){
  stat.isStalled = false;
  ser.requestCommand(HOME); // request home command
  while (ser.isParseReady()==false) {ser.readSerial();} //read serial until received
  ser.parseCommand(&qdStepCommand,&stat); //parse home command
  steppers.beginCommand(&qdStepCommand); //do home command
  while (stat.isStalled == false) {Serial.println(stat.isStalled);} // wait for command to finish
  
  ser.requestCommand(BACKUP); // request backup command
  while (ser.isParseReady()==false) {ser.readSerial();} //read serial until received
  ser.parseCommand(&qdStepCommand,&stat); //parse home command
  steppers.beginCommand(&qdStepCommand); //do backup command
  while (steppers.isCommandDone()==false) {} // wait for command to finish

   
  stat.angularStepPosition = 0; //set angular position to max position
  stat.radialStepPosition = 50000; //set radial position to max position

  //prep table to be active again
  stat.isCommandActive = false;
  stat.isCommandQd = false;
  stat.isCommandRequested = false;
  stat.isHomed = true;

  Serial.println("Table homed!");
  
  //tell pi table has been homed?

}






// CommandHandler com;
void setup(){
  
  //setup steppers
  steppers.setup();
  //setup interrupt pin
  attachInterrupt(digitalPinToInterrupt(DIAG_PIN), stall, RISING);
  // setup serial connection with pi 
  ser.setup();


  // set intitial state of table
  stat.isCommandActive = false;
  stat.isCommandQd = false;
  stat.isCommandRequested = false;
  stat.isHomed = false;
  debugPrintTime = 0;
}

//test loop 



//main loop for table
void loop(){
  if(stat.isHomed==false){
    home();
  }
  else{
  //check if a command is active
  if(stat.isCommandActive == false){
    if(stat.isCommandQd == true){
      radialISRcalls = 0;
      angularISRcalls = 0;
      steppers.beginCommand(&qdStepCommand); //begin qd step command
      stat.isCommandActive = true;
      stat.isCommandQd = false;
      stat.isCommandRequested = false;
    }
    else{
      if(stat.isCommandRequested == false){
        ser.requestCommand(STEP);//request step command to q up
        stat.isCommandRequested = true;
      }
    }
  }
  else{
      if(stat.isCommandQd== false){
        if(stat.isCommandRequested==false){
          ser.requestCommand(0);//request step command to q up
          stat.isCommandRequested = true;
      }
        }
        
  }
  ser.readSerial();// read serial port 

  //check if there is command ready to be parse
  if(ser.isParseReady()==true){ 
    ser.parseCommand(&qdStepCommand,&stat); //parses command and set qdCommand accordingly
    stat.isCommandQd = true;
  }
  //check if step command has finished
  if(steppers.isCommandDone()==true){
    stat.isCommandActive = false;
    // Serial.println("COMMAND FINISHED");
  }
  
    // Serial.print("Command Active: ");
    // Serial.print(stat.isCommandActive);
    // Serial.print("   Command Qd: ");
    // Serial.print(stat.isCommandQd);
    // Serial.print("   Command Requested: ");
    // Serial.print(stat.isCommandRequested);
    // Serial.print("   Radial ISR calls: ");
    // Serial.print(radialISRcalls);
    // Serial.print("  Angular ISR calls: ");
    // Serial.println(angularISRcalls);
  }
}






// void loop(){
//   // checks if a step command is being executed
//   if(com.isCommandActive()==false){
//     if(com.isCommandQd()==true){
//       stepCommand* ptr; // step command pointer
//       com.activateQdCommand(ptr); //command handler activates command and pointer points to qD command 
//       steppers.beginCommand(ptr); //steppers begins executing activated command
//     }
//   }

//   ser.readSerial(); // read serial 
//   //check if there is a command ready to be parsed in serial buffer 
//   if(ser.isParseReady()==true){
//     //TODO fix to do in terms of pointers since I can't actually do it like this
//     com.parseSerial(ser.getreceivedChars());//parse command in serial buffer
//   }
//   //check if there is command queud up to be executed
//   if(com.isCommandQd()==false){
//     ser.requestCommand(0);//request command if no command is queued
//   }

// }
