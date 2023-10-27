#include "Light.h"
#include <Arduino.h>

Light::Light(long clength){
    duration = clength;
    lightElapsed = 0;
    pinMode(13,OUTPUT);
    digitalWrite(13,LOW);
    
}

int Light::run(){
    if(lightElapsed < duration){
        digitalWrite(13,HIGH);
        return 1;
    }
    else{
        Serial.println("writing led low");
        digitalWrite(13,LOW);
        return 0;
    }
}

int Light::set(long command_length){
    lightElapsed = 0;
    duration = command_length;
    return 1;
}