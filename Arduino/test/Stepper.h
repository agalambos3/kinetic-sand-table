/*This class is responsible for managing motor movement on hardware levle
-pin declarations
-tmc stepper
*/
#ifndef stepper_
#define stepper_

#include "TMCStepper.h"
#include "elapsedMillis.h"

// serial port for steppers
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
// rms current for steppers 
#define RMS_CURRENT 400
// stall value at which stall guard is triggered. larger value make stall guard less sensitive (counter to what is online?)
#define STALL_VALUE 2 


// microstepping for radial stepper motor
#define RADIAL_MICROSTEPS 16
// number of teeth on radial gear
#define RADIAL_TOOTH_NUMBER 40
// pitch of radial gear in mm
#define RADIAL_PITCH 2
// max speed in mm/s for radial stepper motor 
#define RADIAL_MAX_MM_PER_SECOND 15


// number of microsteps per revolution of stepper
#define RADIAL_STEPS_PER_REVOLUTION RADIAL_MICROSTEPS*200
// mm per revolution for radial gear 
#define RADIAL_MM_PER_REVOLUTION RADIAL_TOOTH_NUMBER*RADIAL_PITCH
// steps per mm for radial gear
const float RADIAL_STEPS_PER_MM = (RADIAL_STEPS_PER_REVOLUTION)/(RADIAL_MM_PER_REVOLUTION);
// maximum number of steps per second for radial stepper
const float RADIAl_MAX_STEPS_PER_SECOND = RADIAL_MAX_MM_PER_SECOND*RADIAL_STEPS_PER_MM;
//minimum amount of time between steps for radial stepper
const float RADIAL_MIN_STEP_INTERVAL = 1/RADIAl_MAX_STEPS_PER_SECOND;
// minimum number of microseconds between radial steps based on max radial speed
const int RADIAL_MIN_MICROSECONDS = RADIAL_MIN_STEP_INTERVAL*1000000;


// microstepping for angular stepper motor 
#define ANGULAR_MICROSTEPS 16
// number of teeth on angular gear
#define ANGULAR_TOOTH_NUMBER 20
// number of teeth on central gear
#define CENTRAL_TOOTH_NUMBER 200
// max speed in degrees/s for angular stepper motor 
#define ANGULAR_MAX_DEGREES_PER_SECOND 10

// ratio of large to small gear 
#define ANGULAR_GEAR_RATIO (CENTRAL_TOOTH_NUMBER)/(ANGULAR_TOOTH_NUMBER)
// number of steps for 1 revolution of arm
#define ANGULAR_STEPS_PER_REVOLUTION  200*ANGULAR_GEAR_RATIO
// number of revolutions per second based on max degrees/s
const float ANGULAR_REVOLUTIONS_PER_SECOND = float(ANGULAR_MAX_DEGREES_PER_SECOND)/360;
// angular steps per second
const float ANGULAR_STEPS_PER_SECOND = ANGULAR_REVOLUTIONS_PER_SECOND*ANGULAR_STEPS_PER_REVOLUTION;
// angular time 
const float ANGULAR_MIN_STEP_INTERVAL = 1/(ANGULAR_MICROSTEPS*ANGULAR_STEPS_PER_SECOND);

// minimum number of microseconds between angular steps based on max angular speed
const float ANGULAR_MIN_MICROSECONDS =  ANGULAR_MIN_STEP_INTERVAL*1000000;



class Steppers {
    long angular_steps = 0;
    long radial_steps= 0;
    double angular_step_interval;
    double radial_step_interval;
    elapsedMicros angular_elapsed_time;
    elapsedMicros radial_elapsed_time;
    
    
    public:
    TMC2209Stepper radialDriver = TMC2209Stepper(&STEPPER_SERIAL_PORT,R_SENSE,RADIAL_DRIVER_ADDRESS);
    TMC2209Stepper angularDriver = TMC2209Stepper(&STEPPER_SERIAL_PORT,R_SENSE,ANGULAR_DRIVER_ADDRESS);
    int setup();
    int run();
    int set(long angular,long radial);
};



#endif