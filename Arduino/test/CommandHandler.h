/*This class is responsible for
-run() called every cycle of main loop and the folllowing must happen
    -check active commands and call their run() functionality 
    -check if command queue has space, if yes ask serial handler to send request
    -add commands to command queue from serial buffer (this means parsing functionality built in here)
    */
#ifndef comhandler
#define comhandler
#include <cppQueue.h>

struct stepCommand
    {
        long angular_steps;
        long radial_steps;
    };

class CommandHandler{
    
    public:
    // TODO figure out size of command objects in queue in bytes so 
    cppQueue stepQ = cppQueue(sizeof(stepCommand),4,FIFO);
    bool isActiveStep;
    int parseCommmand(char bufcommand[]);
    void run();//called each loop of main.ino
    int setup(); // called during set-up
    bool checkQ(); //checks if queue is full
};


#endif