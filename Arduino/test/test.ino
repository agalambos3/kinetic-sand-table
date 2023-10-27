#include "SerialHandler.h"
#include "CommandHandler.h"
#include <Arduino.h>


SerialHandler ser;
CommandHandler com;

void setup() {
  //do setup here
  ser.setup();
  //request command 
  // ser.requestCommand();
  // //parse command and add it to command queue
  // while(ser.commandReady!=true){
  //   ser.readSerial();
  //   }
  // Serial.println("ready command");
  // com.parseCommmand(ser.receivedChars);
  // stepCommand peeked;
  // com.stepQ.pop(&peeked);
  // Serial.print("peeked command is: ");
  // Serial.print(peeked.angular_steps);
  // Serial.print(" angular step, ");
  // Serial.print(peeked.radial_steps);
  // Serial.println(" radial steps");
  // while(false){};
  
  
  //at this point table should have one command it can start running right away rest will fall into place
}

void loop() {

  
  if(com.run()==1){
      ser.requestnum--;
  } //run active command or pop command from queue make active and then run command
   

  ser.readSerial(); //check serial port read and store to buffer 

  if (com.checklightQ() != true && ser.requestnum <=4){ // check if queue is full 
    ser.requestCommand(1); //if queue is not full request command over serial
  }

  if(ser.commandReady == true){ //check if there is command ready to be parsed from buffer
    
    if(com.parseCommmand(ser.receivedChars)== 1){
      Serial.println("command parsed");
    } //parse command from buffer and add it to command queue
    ser.commandReady = false;
  }
}