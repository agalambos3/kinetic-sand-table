/*This class is responsible for 
    -run() called every cycle of main loop and the folllowing must happen
    -check active commands and call their run() functionality 
    -check if command queue has space, if yes ask serial handler to send request
    -add commands to command queue from serial buffer (this means parsing functionality built in here)
    */

#ifndef comhandler
#define comhandler
#include "cppQueue.h"
#include "Light.h"
#include "Stepper.h"


struct stepCommand
    {
        long angular_steps;
        long radial_steps;
    };

struct lightCommand{
    long duration;
};

class CommandHandler{
    Light arduino_light = Light(0);
    Steppers steppers = Steppers();

    public:
    // TODO figure out size of command objects in queue in bytes so 
    cppQueue stepQ = cppQueue(sizeof(stepCommand),4,FIFO);
    cppQueue lightQ = cppQueue(sizeof(lightCommand),4,FIFO);
    bool isActiveStep;
    bool isActiveLight;
    int parseCommmand(char bufcommand[]);
    int run();//called each loop of main.ino returns 1 if command completed in that cycle 
    int setup(); // called during set-up
    bool checkstepQ(); //checks if queue is full
    bool checklightQ();//checks if light queue is full
};


#endif