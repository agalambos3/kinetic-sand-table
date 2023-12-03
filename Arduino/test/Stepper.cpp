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
    angularDriver.SGTHRS(STALL_VALUE);

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
    radialDriver.SGTHRS(STALL_VALUE); //setting threshold for stall guard


    return 1;
}

int Steppers::set(long angular,long radial){
    Serial.println(angular);
    Serial.println(radial);
    if (angular >= 0)
    {
        angularDriver.shaft(true);
    }
    else{
        angularDriver.shaft(false);
    }
    if (radial >= 0)
    {
        radialDriver.shaft(true);
    }
    else{
        radialDriver.shaft(false);
    }
    angular_steps = abs(angular) ;
    radial_steps = abs(radial) ;
    if (angular_steps>radial_steps)
    {
        angular_step_interval = ANGULAR_MIN_MICROSECONDS;
        long move_time = angular_step_interval*angular_steps;
        radial_step_interval = move_time/radial_steps;

    }
    else{
        radial_step_interval = RADIAL_MIN_MICROSECONDS;
        long move_time = radial_step_interval*radial_steps;
        angular_step_interval = move_time/angular_steps;
    }
    radial_elapsed_time = 0;
    angular_elapsed_time = 0;
    return 1;

}

int Steppers::run(){
    if(angular_steps > 0 || radial_steps > 0){
        // Serial.println(angularDriver.SG_RESULT());
        if (angular_steps > 0 && angular_elapsed_time > angular_step_interval)
        {
            digitalWrite(ANGULAR_STEP_PIN,HIGH);
            angular_steps--;
            digitalWrite(ANGULAR_STEP_PIN,LOW);
            angular_elapsed_time -= angular_step_interval;
        }
        if (radial_steps > 0 && radial_elapsed_time > radial_step_interval)
        {
            digitalWrite(RADIAL_STEP_PIN,HIGH);
            radial_steps--;
            digitalWrite(RADIAL_STEP_PIN,LOW);
            radial_elapsed_time -= radial_step_interval;
            

        }
        return 0;
        
    } 
    else{
        return 1; // command is over return letting commandhandler know that this is the case 
    }
}