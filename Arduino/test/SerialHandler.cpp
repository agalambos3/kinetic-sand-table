#include "SerialHandler.h"
#include "CommandHandler.h"
#include <Arduino.h>


char SerialHandler::giveChar(){
    return 'a';
}

void SerialHandler::setup(){
    Serial.begin(115200);
    Serial.write("s");
    recieveReady = true;
    Serial.write("r");
}

void SerialHandler::readCommand(){
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

int SerialHandler::parseCommand(char bufcommand[]){
    // TODO: rewrite with switch syntax bkecause it will be easier to follow and understand
    if (bufcommand[0] == 'S'){
        char stepchar_radial[5]= {};
        char stepchar_angular[5] = {};
        long steps_radial;
        long steps_angular;
        if (bufcommand[1] == ' '){
            int indx = 2;
            int rindx = 0;
            while(bufcommand[indx]!= ' ' || rindx < 5){
                
                stepchar_radial[rindx] = bufcommand[indx];
                indx++;
                rindx++;
            }
            if (bufcommand[indx] == ' '){
                indx++;
                int aindx = 0;
                while(bufcommand[indx] != ' ' || aindx < 5)
                {
                    stepchar_angular[aindx]= bufcommand[indx];
                    indx++;
                    aindx++;
                }
            }
        steps_radial = atol(stepchar_radial);
        steps_angular = atol(stepchar_angular);
        }
        Serial.println(stepchar_radial);
        Serial.println(stepchar_angular);
        Serial.println(steps_radial);
        Serial.println(steps_angular);
        // Serial.write("Step command recieved. Radial move is");
        // Serial.write(steps_radial);
        // Serial.write(" step");

    }

}