#include "Stepper.h"

int Steppers::setup(){

    //  setup pins for angular driver
    pinMode(ANGULAR_STEP_PIN,OUTPUT);
    pinMode(ANGULAR_DIR_PIN,OUTPUT);
    pinMode(ANGULAR_EN_PIN,OUTPUT);

    //enable angular driver in hardware
    digitalWrite(ANGULAR_EN_PIN,LOW); 

    // intialize HW UART and angular driver 
    ANGULAR_SERIAL_PORT.begin(115200);
    angularDriver.begin();

    // UART settings for angular driver
    angularDriver.toff(5);
    angularDriver.rms_current(400);
    angularDriver.microsteps(16);
    angularDriver.en_spreadCycle(false);
    angularDriver.pwm_autoscale(true);

    // setup pins for radial driver
    pinMode(RADIAL_STEP_PIN,OUTPUT);
    pinMode(RADIAL_DIR_PIN,OUTPUT);
    pinMode(RADIAL_EN_PIN,OUTPUT);

    //enable radial driver in hardware
    digitalWrite(RADIAL_EN_PIN,LOW);

    // intialize HW UART and angular driver
    RADIAL_SERIAL_PORT.begin(115200);
    radialDriver.begin();

    // UART settings for angular driver
    radialDriver.toff(5);
    radialDriver.rms_current(400);
    radialDriver.microsteps(16);
    radialDriver.en_spreadCycle(false);
    radialDriver.pwm_autoscale(true);


    return 1;
}

int Steppers::set(long angular,long radial){
    angular_steps = angular;
    radial_steps = radial;

    return 1;

}
