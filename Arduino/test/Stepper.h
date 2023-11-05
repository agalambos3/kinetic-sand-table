/*This class is responsible for managing motor movement on hardware levle
-pin declarations
-tmc stepper
*/
#ifndef stepper_
#define stepper_

#include "TMCStepper.h"

// pin defintions for angular stepper driver
#define ANGULAR_EN_PIN 7 
#define ANGULAR_DIR_PIN 6 
#define ANGULAR_STEP_PIN 5

// serial defintions for angular stepper driver
#define ANGULAR_SERIAL_PORT Serial1
#define ANGULAR_DRIVER_ADDRESS 0b00

// pin defitions for radial stepper driver
#define RADIAL_EN_PIN 4 
#define RADIAL_DIR_PIN 3 
#define RADIAL_STEP_PIN 2

// serial definitions for radial stepper driver
#define RADIAL_SERIAL_PORT Serial2
#define RADIAL_DRIVER_ADDRESS 0b00


#define R_SENSE 0.11f

class Steppers {
    public:
    TMC2209Stepper radialDriver = TMC2209Stepper(&RADIAL_SERIAL_PORT,R_SENSE,RADIAL_DRIVER_ADDRESS);
    TMC2209Stepper angularDriver = TMC2209Stepper(&ANGULAR_SERIAL_PORT,R_SENSE,ANGULAR_DRIVER_ADDRESS);
    int setup();
    
};



#endif