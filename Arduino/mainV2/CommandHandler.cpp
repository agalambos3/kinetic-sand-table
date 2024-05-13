#include "CommandHandler.h"

bool CommandHandler::isCommandActive(){
  return commandActive;
}

bool CommandHandler::isCommandQd(){
  return commandQd;
}

void CommandHandler::parseSerial(char receivedChars){

}

void CommandHandler::activateQdCommand(stepCommand* ptr){
  ptr = &qdCommand;
  commandActive = true;
  commandQd = false;
}