#include "comtest.h"

Arduinocomms com;

void setup() {
  //do setup here
  com.setup();
}

void loop() {
  com.readCommand();
  if(com.commandReady == true){
    Serial.write(com.receivedChars);
    com.commandReady = false;
  }
}