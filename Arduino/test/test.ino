#include "SerialHandler.h"
#include "CommandHandler.h"

 

SerialHandler ser;
CommandHandler com;

void setup() {
  //do setup here
  ser.setup();
  //request command 
  ser.requestCommand();
  //parse command and add it to command queue
  com.parseCommmand();
  //at this point table should have one command it can start running right away rest will fall into place
}

void loop() {

  com.run(); //run active command or pop command from queue make active and then run command 

  ser.readSerial(); //check serial port read and store to buffer command

  if (com.checkQ() != true){ // check if queue is full 
    ser.requestCommand(); //if queue is not full request command over serial
  }

  if(ser.commandReady == true){ //check if there is command ready to be parsed from buffer
    com.parseCommmand(); //parse command from buffer and add it to command queue
    ser.commandReady = false;
  }
}