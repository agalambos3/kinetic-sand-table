/*This class is responsible for:
-setting up serial connection with python
-requesting commands to be sent
-confirming commands are receieved
-confirming commmands have finished executing*/
#ifndef serhandler
#define serhandler

class SerialHandler {
    static const int numChars = 15;
    static const int cqsize = 5;
    bool isRecieving;
    
    
    public: 
        bool recieveReady; //whether serial is ready to receieve
        char receivedChars[numChars]; //serial buffer
        bool commandReady = false;//if command is sitting in serial buffer ready to be parsed 

    char giveChar(); //test function that returns character
    void setup(); //setup communication
    void readSerial(); //read serial and stores in buffer
    int requestCommand(); // requests a type of command to be sent over serial
    int completedCommand();//sends a character indicating the completion of a succesful command
    int parseCommand(char bufcommand[]); //transferred over to CommandHandler
        
};


#endif