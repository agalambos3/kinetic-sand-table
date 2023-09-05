/*Main document for running arduino. For now I will put all functions in one big ugly docuement. TODO: once commuication
is working split up stuff into different .cpp files so that it is easier to keep track of everything*/

#include "communication.h"

void setup() {
  //do setup here
  Serial.begin(115200);
  //communicate that set-up is succesful
  Serial.write("s");
  recieve_ready = true;
}

void loop() {
  recvWithStartEndMarkers();
  if(newCommand==true){
    Serial.print("I recieved: ");
    Serial.println(receivedChars);
  }
}