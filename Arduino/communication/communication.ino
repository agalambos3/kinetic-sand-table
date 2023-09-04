/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

#include <elapsedMillis.h>

// Global variables needed for table communication
static bool recieve_ready = false; //whether table is ready to receive over serial
elapsedMillis commandtime; 
const byte numChars = 15; //maximum number of characters command will be
char receivedChars[numChars]; //array for storing recieved command
boolean newCommand = false;//whether there is new command that is ready to be parsed and executed


// the setup function runs once when you press reset or power the board
void setup() {
  //do setup here
  Serial.begin(115200);
  //communicate that set-up is succesful
  Serial.write("s");
  recieve_ready = true;
}


// the loop function runs over and over again forever
void loop() {
  recvWithStartEndMarkers();
  if(newCommand==true){
    Serial.print("I recieved: ");
    Serial.println(receivedChars);
  }
}

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
    while (Serial.available() > 0 && newCommand == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newCommand = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}


/*Components I need:
Command reader - reads bytes from serial line and turns them into a char array. Should be called every time in loop that there is data in the serial port 
Command parser - command parser takes char array returned by command reader and sets variables in order for command to execute
(for example sets move to specific value)
*/