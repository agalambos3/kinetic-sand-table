#ifndef serhandler
#define serhandler

class SerialHandler {
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
    int requestCommand(); // requests a type of command to be sent over serial
    int completedCommand();//sends a character indicating the completion of a succesful command
    int parseCommand(char bufcommand[numChars]); //takes command from buffer and parses it 
        
};


#endif