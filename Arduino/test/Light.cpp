#include "Light.h"
#include <Arduino.h>

Light::Light(long clength){
    duration = clength;
    lightElapsed = 0;
    pinMode(13,LOW);
}

int Light::run(){
    if(lightElapsed < duration){
        pinMode(13,HIGH);
        return 1;
    }
    else{
        pinMode(13,LOW);
        lightElapsed = 0;
        return 0;
    }
}

int Light::set(long command_length){
    duration = command_length;
    return 1;
}