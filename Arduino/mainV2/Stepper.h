#ifndef STEPPER_H
#define STEPPER_H

#include "Arduino.h"
#include "TMCStepper.h"
#include "elapsedMillis.h"



// serial port for stepper driver 
#define STEPPER_SERIAL_PORT Serial1

// pin definitions for angular stepper driver
#define ANGULAR_EN_PIN 6 
#define ANGULAR_DIR_PIN 5 
#define ANGULAR_STEP_PIN 4

// serial address for angular stepper driver
#define ANGULAR_DRIVER_ADDRESS 0b00

// pin defitions for radial stepper driver
#define RADIAL_EN_PIN 9 
#define RADIAL_DIR_PIN 8 
#define RADIAL_STEP_PIN 7
#define RADIAL_DIAG_PIN 3

// serial address for radial stepper driver
#define RADIAL_DRIVER_ADDRESS 0b01


// internal resistor setting for TMC2209 so that current can be controlled through UART
#define R_SENSE 0.11f
// rms current for steppers (in milliamps)
#define RMS_CURRENT 100
// microstepping for angular stepper motor 
#define MICROSTEPS 16
// stall value at which stall guard is triggered
#define STALL_VALUE 80
// minimum time (in ms) between stall events (used for simple debouncing of diag pin) 
#define MIN_STALL_TIME 100


struct stepCommand{
    long radialStepGoal;
    long radialTimerCount;
    long angularStepGoal;
    long angularTimerCount;
  };


class StepperHandler{
  TMC2209Stepper radialDriver = TMC2209Stepper(&STEPPER_SERIAL_PORT,R_SENSE,RADIAL_DRIVER_ADDRESS);
  TMC2209Stepper angularDriver = TMC2209Stepper(&STEPPER_SERIAL_PORT,R_SENSE,ANGULAR_DRIVER_ADDRESS);
  stepCommand qdCommand;
  public:
  int setup();
  void beginRadialCommand(long radialTout,long stepgoal);
  void setqdCommand(long radialStepGoal, long radialTimerCount,long angularStepGoal, long angularTimerCount);
  void beginqdCommand();
  
  
};

#endif



