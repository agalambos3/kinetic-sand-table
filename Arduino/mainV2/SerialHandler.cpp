#include "USBCore.h"
#include "SerialHandler.h"
#include <Arduino.h>


char SerialHandler::giveChar(){
    return 'a';
}

void SerialHandler::setup(){
    while (!Serial) {;} // wait for serial port to connect. Needed for native USB port only
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
    while (Serial.available() > 0 && parseReady == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= NUMCHARS) {
                    ndx = NUMCHARS - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                parseReady = true;
            }
        }
        
        else if (rc == startMarker) {
            recvInProgress = true;
        }

    }

}




void SerialHandler::parseValue(int* ptrIndx, char targetChar[8],int maxValIndx){
  int valIndx = 0;
  while (receivedChars[*ptrIndx] != ' ') {
    (targetChar)[valIndx] = receivedChars[*ptrIndx];
    (*ptrIndx)++;
    valIndx ++;
    if(valIndx > maxValIndx){
      break;
    }

  }
}




void SerialHandler::parseCommand(struct stepCommand* stepPtr,struct tableStatus* statPtr){
  switch (receivedChars[0] ) {
    case 'S': //step command
    {

      char parsedRadialStepGoal[8] = {};
      char parsedRadialTimerOut[8] = {};
      char parsedAngularStepGoal[8] = {};
      char parsedAngularTimerOut[8] = {};

      int maxValIndx = 7;
      int indx = 2;
      parseValue(&indx, parsedRadialStepGoal,maxValIndx);
      indx ++;
      parseValue(&indx,parsedRadialTimerOut,maxValIndx);
      indx ++;
      parseValue(&indx,parsedAngularStepGoal,maxValIndx);
      indx++;
      parseValue(&indx,parsedAngularTimerOut,maxValIndx);

      (*stepPtr).radialStepGoal = atol(parsedRadialStepGoal);
      (*stepPtr).radialTimerCount = atol(parsedRadialTimerOut);
      (*stepPtr).angularStepGoal = atol(parsedAngularStepGoal);
      (*stepPtr).angularTimerCount = atol(parsedAngularTimerOut);
      Serial.println("step command parsed");
      parseReady = false;
      break;
      }
    case 'P': //position command
    {
      //characters to store parsed theta and r
      char parsedTheta[9] = {};
      char parsedR[9] = {};

      //floats to store parsed theta and r 
      float theta;
      float R;

      //floats to store dif in position
      float delTheta;
      float delR;

      int maxValIndx = 9;
      int indx =2;

      parseValue(&indx,parsedTheta,maxValIndx);
      indx++;
      parseValue(&indx, parsedR, maxValIndx);

      theta = atof(parsedTheta);
      R = atof(parsedR);

      delTheta = theta-(*statPtr).previousTheta;
      delR = R-(*statPtr).previousR;

      //set goals to zero
      (*stepPtr).angularStepGoal = 0;
      (*stepPtr).radialStepGoal = 0;


      // compute number of steps for del theta

      float angularStepsFloat = (((CENTRAL_GEAR_TEETH/ANGULAR_STEPPER_TEETH)*NEMA17_STEPS_PER_REVOLUTION*MICROSTEPS)/PI)*delTheta;

      (*stepPtr).angularStepGoal += angularStepsFloat;
      (*stepPtr).radialStepGoal += angularStepsFloat/8;
      


      //compute number of steps for del R

      (*stepPtr).radialStepGoal += delR*((*statPtr).stepDiam/2);

      
      //compute angular stepping speed

      //compute radial stepping speed

      



      break;
    }

    default:
      parseReady = false;
      Serial.println("no matching command case found");

    }
    
    
}
  

void SerialHandler::requestCommand(commandType command){
    requestnum++;
    switch (command)
    {
    case HOME:
        Serial.write("H\n");
        break;
    case BACKUP:
        Serial.write("B\n");
        break;
    case STEP:
        Serial.write("S\n");
        break;
    
    case LIGHT:
        Serial.write("L\n");
        break;
    }
    
  
    
}

int SerialHandler::completedCommand(){
    return 0;
}

char SerialHandler::getreceivedChars(){
    return receivedChars;
}

bool SerialHandler::isParseReady(){
  return parseReady;
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