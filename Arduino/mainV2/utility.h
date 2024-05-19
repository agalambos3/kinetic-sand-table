#ifndef UTILITY_H
#define UTILITY_H

struct stepCommand{
    long radialStepGoal;
    long radialTimerCount;
    long angularStepGoal;
    long angularTimerCount;
  };

struct tableStatus{
    bool isCommandActive;
    bool isCommandRequested;
    bool isCommandQd;
    bool isHomed;
  };

#endif