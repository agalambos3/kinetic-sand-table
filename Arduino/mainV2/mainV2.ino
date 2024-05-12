#include "SerialHandler.h"
#include "Stepper.h"



bool isCommandActive;
bool isCommandReady;
bool isHomed;
bool isCommandQd;


SerialHandler ser;
StepperHandler steppers;
void setup(){
  ser.setup();
  

}

void loop(){
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