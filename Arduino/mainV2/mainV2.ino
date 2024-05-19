#include "SerialHandler.h"
// #include "CommandHandler.h"
#include "Stepper.h"



struct tableStatus stat; // structure for managing state of table 

struct stepCommand qdStepCommand; //qD stepcommand struct


class StepperHandler steppers; //initialize stepper handler
class SerialHandler ser; // intialize serial handler






//ISR for radial step movement
ISR(TIMER3_COMPA_vect){
  steppers.radialStepISR();
}

//ISR for angular step movement
ISR(TIMER3_COMPB_vect){
  steppers.angularStepISR();
}



// CommandHandler com;
void setup(){
  // set intitial state of table
  stat.isCommandActive = false;
  stat.isCommandQd = false;
  stat.isCommandRequested = false;
  stat.isHomed = false;
  //setup steppers
  steppers.setup();
  // setup serial connection with pi 
  ser.setup();
}

//main loop for table
void loop(){
  //check if a command is active
  if(stat.isCommandActive == false){
    if(stat.isCommandQd == true){
      steppers.beginCommand(&qdStepCommand); //begin qd step command
      stat.isCommandQd == false;
      stat.isCommandRequested = false;
    }
    else{
      if(stat.isCommandRequested == false){
        ser.requestCommand(0);//request step command to q up
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
    ser.parseCommand(&qdStepCommand); //parses command and set qdCommand accordingly
    stat.isCommandQd = true;
  }
  //check if step command has finished
  if(steppers.isCommandDone()==true){
    stat.isCommandActive = false;
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
