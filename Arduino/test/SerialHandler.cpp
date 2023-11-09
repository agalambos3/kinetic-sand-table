#include "SerialHandler.h"
#include <Arduino.h>


char SerialHandler::giveChar(){
    return 'a';
}

void SerialHandler::setup(){
    // begin serial communication
    Serial.begin(115200);
    Serial.write("R");
}

void SerialHandler::readSerial(){
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



// TODO move over to command handler 
// void SerialHandler::parseCommand(char bufcommand[]){
//     // TODO: rewrite with switch syntax because it will be easier to follow and understand
//     if (bufcommand[0] == 'S'){
//         char stepchar_radial[6]= {};
//         char stepchar_angular[6] = {};
//         long steps_radial;
//         long steps_angular;
//         if (bufcommand[1] == ' '){
//             int indx = 2;
//             int rindx = 0;
//             while(bufcommand[indx]!= ' ' && rindx < 6){
                
//                 stepchar_radial[rindx] = bufcommand[indx];
//                 indx++;
//                 rindx++;
//             }
//             if (bufcommand[indx] == ' '){
//                 indx++;
//                 int aindx = 0;
//                 while(bufcommand[indx] != ' ' && aindx < 6)
//                 {
//                     stepchar_angular[aindx]= bufcommand[indx];
//                     indx++;
//                     aindx++;
//                 }
//             }
//         steps_radial = atol(stepchar_radial);
//         steps_angular = atol(stepchar_angular);
//         }
//         Serial.println(stepchar_radial);
//         Serial.println(stepchar_angular);
//         Serial.println(steps_radial);
//         Serial.println(steps_angular);
//         // Serial.write("Step command recieved. Radial move is");
//         // Serial.write(steps_radial);
//         // Serial.write(" step");

//     }

// }

void SerialHandler::requestCommand(int command_type){
    requestnum++;
    switch (command_type)
    {
    case 0:
        Serial.write("S\n");
        break;
    
    case 1:
        Serial.write("L\n");
        break;
    }
}

int SerialHandler::completedCommand(){
    return 0;
}

