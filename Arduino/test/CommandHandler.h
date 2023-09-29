/*This class is responsible for
-run() called every cycle of main loop and the folllowing must happen
    -check active commands and call their run() functionality 
    -check if command queue has space, if yes ask serial handler to send request
    -add commands to command queue from serial buffer (this means parsing functionality built in here)
    */
#ifndef comhandler
#define comhandler
#include "Command.h"
class CommandHandler{
    
    
    public:
    bool isActiveStep;
    int parseCommmand();
    void run();//called each loop of main.ino

};


#endif