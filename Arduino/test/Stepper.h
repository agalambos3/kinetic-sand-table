/*This class is responsible for managing motor movement on hardware levle
-pin declarations
-tmc stepper
*/
#ifndef stepper_
#define stepper_

#include "TMCStepper.h"
#include "elapsedMillis.h"

// pin defintions for angular stepper driver
#define ANGULAR_EN_PIN 9 
#define ANGULAR_DIR_PIN 8 
#define ANGULAR_STEP_PIN 7

// serial defintions for angular stepper driver
#define ANGULAR_SERIAL_PORT Serial1
#define ANGULAR_DRIVER_ADDRESS 0b00

// pin defitions for radial stepper driver
#define RADIAL_EN_PIN 6 
#define RADIAL_DIR_PIN 5 
#define RADIAL_STEP_PIN 4

// serial definitions for radial stepper driver
#define RADIAL_SERIAL_PORT Serial1
#define RADIAL_DRIVER_ADDRESS 0b01

// internal resistor setting for TMC2209 so that current can be controlled through UART
#define R_SENSE 0.11f

// stall value at which stall guard is triggered. larger value make stall guard less sensitive 
#define STALL_VALUE 100 

// microstepping for radial stepper motor
#define RADIAL_MICROSTEPS 16
// max speed in mm/s for radial stepper motor 
#define RADIAL_MAX_MM_PER_SECOND 1
// mm per step for radial motor (.02 comes from gt2 gear profile)
#define RADIAL_MM_PER_STEP .02
const float RADIAL__TIME_PER_MICROSTEP = RADIAL_MM_PER_STEP/RADIAL_MAX_MM_PER_SECOND/RADIAL_MICROSTEPS;

// minimum number of microseconds between radial steps based on max radial speed
const float RADIAL_MIN_MICROSECONDS = RADIAL__TIME_PER_MICROSTEP*1000000;




// microstepping for angular stepper motor 
#define ANGULAR_MICROSTEPS 16
// max speed in degrees/s for angular stepper motor 
#define ANGULAR_MAX_DEGREES_PER_SECOND 18
// ratio of large to small gear (8 -> 8:1 ratio)
#define ANGULAR_GEAR_RATIO 8
// number of steps for 1 revolution of arm
#define ANGULAR_STEPS_PER_REVOLUTION  200*ANGULAR_GEAR_RATIO
// number of revolutions per second based on max degrees/s
const float ANGULAR_REVOLUTIONS_PER_SECOND = float(ANGULAR_MAX_DEGREES_PER_SECOND)/360;
// angular steps per second
const float ANGULAR_STEPS_PER_SECOND = ANGULAR_REVOLUTIONS_PER_SECOND*ANGULAR_STEPS_PER_REVOLUTION;
// angular time 
const float ANGULAR__TIME_PER_MICROSTEP = 1/(ANGULAR_MICROSTEPS*ANGULAR_STEPS_PER_SECOND);

// minimum number of microseconds between angular steps based on max angular speed
const float ANGULAR_MIN_MICROSECONDS =  ANGULAR__TIME_PER_MICROSTEP*1000000;


/*TODO: fix all the bullshit with the defines. Defines cannot do math and it is a bad idea. Use define for constatns but do all math in a setup function or something.*/

class Steppers {
    long angular_steps = 0;
    long radial_steps= 0;
    double angular_step_interval;
    double radial_step_interval;
    elapsedMicros angular_elapsed_time;
    elapsedMicros radial_elapsed_time;
    
    
    public:
    TMC2209Stepper radialDriver = TMC2209Stepper(&RADIAL_SERIAL_PORT,R_SENSE,RADIAL_DRIVER_ADDRESS);
    TMC2209Stepper angularDriver = TMC2209Stepper(&ANGULAR_SERIAL_PORT,R_SENSE,ANGULAR_DRIVER_ADDRESS);
    int setup();
    int run();
    int set(long angular,long radial);
};



#endif