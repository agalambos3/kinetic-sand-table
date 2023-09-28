#include "SerialHandler.h"

SerialHandler com;

void setup() {
  //do setup here
  com.setup();
}

void loop() {
  com.readCommand();
  if(com.commandReady == true){
    Serial.write(com.receivedChars);
    Serial.write("\n");
    com.parseCommand(com.receivedChars);
    com.commandReady = false;
  }
}