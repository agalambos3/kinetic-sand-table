#include "comtest.h"

Arduinocomms com;

void setup() {
  //do setup here
  Serial.begin(115200);
  Serial.write("Setup!");
  
}

void loop() {
Serial.write(com.giveChar());
}