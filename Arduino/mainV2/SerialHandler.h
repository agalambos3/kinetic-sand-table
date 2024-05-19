/*This class is responsible for:
-setting up serial connection with python
-requesting commands to be sent
-confirming commands are receieved
-confirming commmands have finished executing*/
#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include "utility.h"

#define NUMCHARS 35 // number of characters in serial buffer
#define CQSIZE 5
 
class SerialHandler {
    bool isRecieving;
    bool parseReady = false;//if command is sitting in serial buffer ready to be parsed
    int requestnum; //number of requests made without a response 
    char receivedChars[NUMCHARS]; //received characters
    void parseValue(int* startIndex, char targetChar[8]); // helper function used in parseCommand to to parse specific value
    void position2Step();
    
    public: 
    char giveChar(); //test function that returns character
    void setup(); //setup communication
    void readSerial(); //read serial and stores in buffer
    void parseCommand(struct stepCommand* ptr);
    void requestCommand(commandType command); // requests a type of command to be sent over serial
    char getreceivedChars();
    bool isParseReady();
    int completedCommand();//sends a character indicating the completion of a succesful command
        
};


#endif