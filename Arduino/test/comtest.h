#ifndef comtest
#define comtest

class Arduinocomms {
    static const int numChars = 15;
    static const int cqsize = 5;
    
    bool isRecieving;
    struct command 
    {
        int radial_steps;
        int angular_steps;
        /* data */
    };//structure
    
    public: 
        command command_queue[cqsize];
        bool recieveReady;
        char receivedChars[numChars];
        bool commandReady = false;

    char giveChar(); //test function that returns character
    void setup(); //setup communication
    void readCommand(); //read serial and stores in buffer
    int parseCommand(); //takes command from buffer and parses it 
        
};


#endif