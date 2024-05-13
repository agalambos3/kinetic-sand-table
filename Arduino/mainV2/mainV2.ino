#include "SerialHandler.h"
#include "CommandHandler.h"
#include "Stepper.h"



bool isHomed;


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
    //TODO fix to do in terms of pointers since I can't actually do it like this
    com.parseSerial(ser.getreceivedChars());//parse command in serial buffer
  }
  //check if there is command queud up to be executed
  if(com.isCommandQd()==false){
    ser.requestCommand(0);//request command if no command is queued
  }

}

ISR(TIMER3_COMPA_vect){
  steppers.radialStepISR();
}

ISR(TIMER3_COMPB_vect){
  steppers.angularStepISR();
}
