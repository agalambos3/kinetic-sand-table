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
    if (angular > 0)
    {
        angularDriver.shaft(true);
    }
    else{
        angularDriver.shaft(false);
    }
    if (radial > 0)
    {
        radialDriver.shaft(true);
    }
    else{
        radialDriver.shaft(false);
    }
    if (angular>radial)
    {
        angular_step_interval = ANGULAR__TIME_PER_MICROSTEP;
        long move_time = angular_step_interval*angular;
        radial_step_interval = move_time/radial;

    }
    else{
        radial_step_interval = RADIAL__TIME_PER_MICROSTEP;
        long move_time = radial_step_interval*radial;
        angular_step_interval = move_time/angular;
    }
    
    angular_steps = angular;
    radial_steps = radial;
    radial_elapsed_time = 0;
    angular_elapsed_time = 0;
    return 1;

}

int Steppers::run(){
    if(angular_steps > 0 || radial_steps > 0){
        if (angular_steps >0 && angular_elapsed_time > angular_step_interval)
        {
            digitalWrite(ANGULAR_STEP_PIN,HIGH);
            digitalWrite(ANGULAR_STEP_PIN,LOW);
            angular_steps--;
            angular_elapsed_time -= angular_step_interval;
        }
        if (radial_steps > 0 && radial_elapsed_time > radial_step_interval)
        {
            digitalWrite(RADIAL_STEP_PIN,HIGH);
            digitalWrite(RADIAL_STEP_PIN,LOW);
            radial_steps--;
            radial_elapsed_time -= radial_step_interval;

        }
        return 0;
        
    } 
    else{
        Serial.println("step command is over");
        return 1; // command is over return letting commandhandler know that this is the case 
    }
}