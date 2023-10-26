#include "CommandHandler.h"
#include <Arduino.h>

int CommandHandler::setup()
{

}

void CommandHandler::run(){
    if(isActiveLight == true){
        // if there is active comand do  command
        if(arduino_light.run()==0){
            isActiveLight == false;
        }
    }
    else{
        // if no active command pop from queue and set command class to command 
        lightCommand active_light;
        lightQ.pop(&active_light);
        arduino_light.set(active_light.duration);
        isActiveLight = true;
        
    }

    }
     

int CommandHandler::parseCommmand(char bufcommand[])
{
    switch (bufcommand[0])
    {
    case 'S':
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
        

    case 'L':
        /*add code to parse light command. This is for testing purposese.
        command should take form <L 3000>. This translates to light being on for 3000 milliseconds.
        Also shold have command that turns light off (in order to test interupting of command). Something like <L X >*/

        return 1;    
    }
    return 0;
}

bool CommandHandler::checkQ(){
    return stepQ.isFull();
}

