

#ifndef light
#define light

#include "elapsedMillis.h"

class Light{
    
    public:
    Light(long clength);
    long duration;
    elapsedMillis lightElapsed;
    int run(); //called every loop if there is active command
    int set(long command_length); // called if there is no active command so parameters need to be set 


};
    

#endif