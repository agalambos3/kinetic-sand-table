#include "Light.h"
#include <Arduino.h>

Light::Light(long clength){
    duration = clength;
    lightElapsed = 0;
    pinMode(LED_BUILTIN,OUTPUT);
    digitalWrite(LED_BUILTIN,LOW);
    
}

int Light::run(){
    if(lightElapsed < duration){
        digitalWrite(LED_BUILTIN,HIGH);
        return 1;
    }
    else{
        Serial.println("writing led low");
        digitalWrite(LED_BUILTIN,LOW);
        return 0;
    }
}

int Light::set(long command_length){
    lightElapsed = 0;
    duration = command_length;
    return 1;
}