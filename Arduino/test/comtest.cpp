#include "comtest.h"
#include <Arduino.h>


char Arduinocomms::giveChar(){
    return 'a';
}

void Arduinocomms::setup(){
    Serial.begin(115200);
    Serial.write("s");
    recieveReady = true;
    Serial.write("r");
}

void Arduinocomms::readCommand(){
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
    while (Serial.available() > 0 && commandReady == false) {
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
                commandReady = true;
            }
        }
        
        else if (rc == startMarker) {
            recvInProgress = true;
        }

    }

}

int Arduinocomms::parseCommand(char bufcommand[numChars]){
    if (bufcommand[0] == 'S'){
        if (bufcommand[1 == ' ']){
            int indx = 2;
            while(bufcommand[indx]!= ' '){

            }
        }
        Serial.write("step command recieved\n");

    }

}