#include "CommandHandler.h"
#include <Arduino.h>

int CommandHandler::setup()
{
    return 1;
}

int CommandHandler::run(){
    if(isActiveLight == true){
        if(arduino_light.run()==0){
            isActiveLight = false;
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        // if no active command pop from queue and set command class to command
        if(lightQ.isEmpty()!= true){
            lightCommand active_light;
            if(lightQ.pop(&active_light)==true){
            Serial.println("command popped from lightq to be become active");
            };
            arduino_light.set(active_light.duration);
            isActiveLight = true;
        }
        return 0;
        
    }

    }
     

int CommandHandler::parseCommmand(char bufcommand[])
{
    switch (bufcommand[0])
    {
    case 'L':
    {
        char durationchar[6]={};//char to store read duration 
        long duration; //long for duration of command 
        if (bufcommand[1]=' '){
            int indx = 2;
            int durindx = 0;
            while (bufcommand[indx]!= ' ' && durindx < 6){
                durationchar[durindx] = bufcommand[indx];
                indx++;
                durindx++;
            }
            duration = atol(durationchar);
            lightCommand lc;
            lc.duration = duration;
            
            if(lightQ.push(&lc)==1){
                Serial.println("Light command pushed to q");
            };
            
            return 1;
        }
        else{
            return 0;
        }
    }
        /*add code to parse light command. This is for testing purposese.
        command should take form <L 3000>. This translates to light being on for 3000 milliseconds.
        Also shold have command that turns light off (in order to test interupting of command). Something like <L X >*/
    

    case 'S':
    {
        char stepchar_radial[5]= {};
        char stepchar_angular[5] = {};
        long steps_radial;
        long steps_angular;

        if (bufcommand[1] == ' '){
            int indx = 2;
            int radial_indx = 0;
            while(bufcommand[indx]!= ' ' && radial_indx < 5){
                // Serial.print("read from buffer: ");
                // Serial.println(bufcommand[indx]);
                
                stepchar_radial[radial_indx] = bufcommand[indx];
                indx++;
                radial_indx++;
            }
            if (bufcommand[indx] == ' '){
                indx++;
                int angular_indx = 0;
                while(bufcommand[indx] != ' ' && angular_indx < 5)
                {
                    
                    stepchar_angular[angular_indx]= bufcommand[indx];
                    indx++;
                    angular_indx++;
                }
            }

        steps_radial = atol(stepchar_radial);
        steps_angular = atol(stepchar_angular);
        stepCommand sc;
        sc.radial_steps = steps_radial;
        sc.angular_steps = steps_angular;
        stepQ.push(&sc);
        return 1;
        }
        else{
            return 0;
        }       
    }
    
    }
    Serial.println("no case found in command");
    return 0;
}

bool CommandHandler::checkstepQ(){
    return stepQ.isFull();
}

bool CommandHandler::checklightQ(){
    return lightQ.isFull();
}

