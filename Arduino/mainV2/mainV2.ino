#include "SerialHandler.h"
#include "CommandHandler.h"
#include "Stepper.h"




bool isCommandActive;
bool isCommandReady;
bool isHomed;
bool isCommandQd;


SerialHandler ser;
StepperHandler steppers;
CommandHandler com;
void setup(){
  ser.setup();
  

}

void loop(){
  // checks if a step command is being executed
  if(com.isCommandActive()==false){
    if(com.isCommandQd()==true){
      stepCommand* ptr; // step command pointer
      com.activateQdCommand(ptr); //command handler activates command and pointer points to qD command 
      steppers.beginCommand(ptr); //steppers begins executing activated command
    }
  }


  ser.readSerial(); // read serial 
  //check if there is a command ready to be parsed in serial buffer 
  if(ser.isParseReady()==true){
    com.parseSerial(ser.getreceivedChars());//parse command in serial buffer
  }
  //check if there is command queud up to be executed
  if(com.isCommandQd()==false){
    ser.requestCommand(0);//request command if no command is queued
  }





  if(isCommandActive==false){
    if (isCommandQd== true) {
      steppers.beginqdCommand();
        // begin qd command
        // set isCommandActive to true
        //set is CommandQd to false
    }
    else{
      if(isHomed==true){
        // request command from pi
        //parse command
        //begin qd command
        //set isCommandActive to true
        //set isCommandQd to false
      }
      else{
        //should only be here after stall isr so homing just happening
        //roll back to "max radial position"
        //let pi know system is homed
        //set isHomed to true

      }

    }
  }
  else{
    if (isCommandQd==false) {
      //request command from pi
      //parse command
      //queue command
      //set commandQd to true 
    }
  }
}

