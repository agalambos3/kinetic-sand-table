/*This is class responsible for:
-whenever command handler calls run() on command it executes it
-given information on status of command if command is finished let handler know*/
#ifndef com
#define com

class Command{
    
    public:
    bool isActive;
    bool isFinished;



};

class stepCommand:public Command {
    int var;
    public:
    void run();

};


#endif