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
    volatile float previousTheta;
    volatile float previousR;
    volatile float targetTheta;
    volatile float targetR;
    volatile long stepDiam; //number of steps needed to traverse table

  };

#endif