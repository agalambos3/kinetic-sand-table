#ifndef UTILITY_H
#define UTILITY_H


enum commandType {STEP,HOME,BACKUP,LIGHT,POSITION};

struct stepCommand{
    long radialStepGoal;
    long radialTimerCount;
    long angularStepGoal;
    long angularTimerCount;
  };

struct tableStatus{
    volatile bool isCommandActive;
    volatile bool isCommandRequested;
    volatile bool isCommandQd;
    volatile bool isHomed;
    volatile bool isStalled;
    volatile long radialStepPosition;
    volatile long angularStepPosition;
  };

#endif