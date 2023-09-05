#ifndef communication
#define communication
#include <Arduino.h>
extern bool recieve_ready; //whether table is ready to receive over serial
const byte numChars =15; //maximum number of characters command will be
extern char receivedChars[numChars]; //array for storing recieved command 
extern bool newCommand;//whether there is new command that is ready to be parsed and executed

void recvWithStartEndMarkers();
#endif 