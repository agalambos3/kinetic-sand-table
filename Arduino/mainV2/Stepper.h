#ifndef STEPPER_H
#define STEPPER_H

#include "Arduino.h"
#include "TMCStepper.h"
#include "elapsedMillis.h"
#include "utility.h"
#include "tableParams.h"


#define STEPPER_SERIAL_PORT Serial1 // serial port for stepper driver 

// pin definitions for angular stepper driver
#define ANGULAR_EN_PIN 6 
#define ANGULAR_DIR_PIN 5 
#define ANGULAR_STEP_PIN 4

#define ANGULAR_DRIVER_ADDRESS 0b00 // serial address for angular stepper driver

// pin defitions for radial stepper driver
#define RADIAL_EN_PIN 9 
#define RADIAL_DIR_PIN 8 
#define RADIAL_STEP_PIN 7
#define RADIAL_DIAG_PIN 3

#define RADIAL_DRIVER_ADDRESS 0b01 // serial address for radial stepper driver



#define R_SENSE 0.11f // internal resistor setting for stepper driver (TMC 2209)
#define RMS_CURRENT 800 // rms current for steppers (in milliamps)


#define DIAG_PIN 3 //diag pin used for stallguard interrupt
#define STALL_VALUE 3 // stall value at which stall guard is triggered
#define MIN_STALL_TIME 500 // minimum time (in ms) between stall events (used for simple debouncing of diag pin) 





class StepperHandler{
  TMC2209Stepper radialDriver = TMC2209Stepper(&STEPPER_SERIAL_PORT,R_SENSE,RADIAL_DRIVER_ADDRESS);
  TMC2209Stepper angularDriver = TMC2209Stepper(&STEPPER_SERIAL_PORT,R_SENSE,ANGULAR_DRIVER_ADDRESS);
  volatile long radialSteps;
  volatile long angularSteps;
  volatile bool radialDone;
  volatile bool angularDone;
  volatile bool commandDone;
  elapsedMillis sinceStall;
  stepCommand activeCommand;
  
  public:
  int setup();
  void radialStepISR();
  void angularStepISR();
  void stallISR();
  void beginCommand(stepCommand* ptr);
  bool isCommandDone();
};

#endif



