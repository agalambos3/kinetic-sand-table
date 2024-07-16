#ifndef COMMAND_H
#define COMMAND_H

#include "utility.h"


class CommandHandler{
  bool commandActive;
  bool commandQd;
  stepCommand qdCommand;
  stepCommand parsedCommand;
  
  public:
  bool isCommandActive();
  bool isCommandQd();
  void parseSerial(char receivedChars);
  void activateQdCommand(stepCommand* ptr);
  bool setQdCommand(long radialStepGoal, long radialTimerCount,long angularStepGoal, long angularTimerCount);
  
  void run();

};

#endif