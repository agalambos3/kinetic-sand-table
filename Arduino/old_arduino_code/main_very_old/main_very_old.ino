/*Main document for running arduino. For now I will put all functions in one big ugly docuement. TODO: once commuication
is working split up stuff into different .cpp files so that it is easier to keep track of everything*/

#include "communication.h"
 /* In main.ino I will declare global variables that influence the actions of the table:
 long next_angular_step - how many steps angular_stepper.move() should be set to after current move is completed
 long next_radial_step - how many steps radial_stepper.move() should be set to after current move is completed
 bool homing - if true table will interrupt and home itself before moving on 
 more variables corresponding to control of the lights
 variables corresponding to pins on arduino
 */


void setup() {
  //do setup here
  Serial.begin(115200);
  //communicate that set-up is succesful
  Serial.write('s');
  recieve_ready = true;
  Serial.write('r');
}

void loop() {
  recvWithStartEndMarkers();
  if(newCommand==true){
    Serial.print("I recieved: ");
    Serial.println(receivedChars);
    Serial.write('r');
    newCommand = false;
  }
}