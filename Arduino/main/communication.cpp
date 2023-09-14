#include "communication.h"
#include <Arduino.h>

// TODO: rewrite this to more class based so that its usage in main.ino is easy to follow and makes sense

/*Class should do the following:
read command - should function like recWithStartEndMarkers() but should have stuff like recieved command passed to it
 
*/

bool recieve_ready = false ; //whether table is ready to receive over serial
char receivedChars[numChars]; //array for storing recieved command 
bool newCommand = false;//whether there is new command that is ready to be parsed and executed

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