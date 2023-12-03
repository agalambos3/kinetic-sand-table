#include "SerialHandler.h"
#include "CommandHandler.h"
#include <Arduino.h>


SerialHandler ser;
CommandHandler com;

void setup() {
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
  //do setup here

  // serial setup, character sent to let python know it was succesful
  ser.setup();
  // command handler setups steppers (in future other stuff as well)
  com.setup();
    

  // // request initial light commands
  // for(int i = 0;i<4;i++){
  //   ser.requestCommand(1);
  // }

  // //while light queue is not full read serial and parse command
  // while(com.checklightQ() !=true){
  //   ser.readSerial();
  //   if(ser.commandReady == true){
  //     if(com.parseCommmand(ser.receivedChars)== 1){
  //       Serial.println("command parsed");
  //       ser.commandReady = false;
  //       }
  //     }
      
  //   }
  
  
  
  //at this point table should have one command it can start running right away rest will fall into place
  Serial.println("set-up complete");
  

}
void loop() {

  // run command handler and if command just finished request another command 
  if(com.run()==1){ 
    ser.requestCommand(0);
  }

  ser.readSerial(); //check serial port read and store to buffer 

  if(ser.commandReady == true && com.checklightQ() !=true){ //check if there is command ready to be parsed from buffer and that queue is not full
    if(com.parseCommmand(ser.receivedChars)== 1){
      Serial.println("command parsed");
      ser.commandReady = false;
    } //parse command from buffer and add it to command queue
    
  }
}