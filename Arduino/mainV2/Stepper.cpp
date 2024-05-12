#include "Stepper.h"

int StepperHandler::setup(){
    // initialize HW UART
    STEPPER_SERIAL_PORT.begin(115200);
    //  setup pins for angular driver
    pinMode(ANGULAR_STEP_PIN,OUTPUT);
    pinMode(ANGULAR_DIR_PIN,OUTPUT);
    pinMode(ANGULAR_EN_PIN,OUTPUT);

    //enable angular driver in hardware
    digitalWrite(ANGULAR_EN_PIN,LOW); 
    
    //intialize angular driver 
    angularDriver.begin();

    // UART settings for angular driver
    angularDriver.toff(5);
    angularDriver.rms_current(RMS_CURRENT);
    angularDriver.microsteps(MICROSTEPS);
    angularDriver.en_spreadCycle(false);
    angularDriver.pwm_autoscale(true);

    // setup pins for radial driver
    pinMode(RADIAL_STEP_PIN,OUTPUT);
    pinMode(RADIAL_DIR_PIN,OUTPUT);
    pinMode(RADIAL_EN_PIN,OUTPUT);
    // Does the radial diag pin need to be set as an input?

    //enable radial driver in hardware
    digitalWrite(RADIAL_EN_PIN,LOW);

    

    // intialize radial driver
    radialDriver.begin();

    // UART settings for radial driver
    radialDriver.toff(5); //TODO: check what this value should be to get consistent stallguard results
    radialDriver.rms_current(RMS_CURRENT);
    radialDriver.microsteps(MICROSTEPS);
    radialDriver.en_spreadCycle(false);
    radialDriver.pwm_autoscale(true);
    radialDriver.SGTHRS(STALL_VALUE); //setting threshold for stall guard
    

    // //  set up timer for radial stepper
    // TCCR3A = 0;           // Init Timer3
    // TCCR3B = 0;           // Init Timer3
    // TCCR3B |= (1 << CS10); //set Timer3 prescalar to 1
    // OCR3A = radialTimerTout;        // Timer3 CompareA Register
    return 1;
}

//sets the queued command
void StepperHandler::setqdCommand(long radialStepGoal, long radialTimerCount,long angularStepGoal, long angularTimerCount){
  qdCommand.radialStepGoal = radialStepGoal;
  qdCommand.radialTimerCount = radialTimerCount;
  qdCommand.angularStepGoal = angularStepGoal;
  qdCommand.angularTimerCount = angularTimerCount;

}

long StepperHandler::getRadialSteps(){
  return radialSteps;
}

//starts queued command
void StepperHandler::beginqdCommand(){
  activeCommand = qdCommand;
  //set up timer for radial direction
  TCCR3A = 0;           // Init Timer3
  TCCR3B = 0;           // Init Timer3
  TCCR3B |= (1 << CS10); //set Timer3 prescalar to 1
  OCR3A = activeCommand.radialTimerCount;  // Timer3 CompareA Register
  // TODO add code for angular direction 
  
}



// ISR for stepper movement

// ISR(TIMER3_COMPA_vect){
//   if(getRadialSteps()<radialStepGoal){
//     digitalWrite(RADIAL_STEP_PIN, HIGH);
//     digitalWrite(RADIAL_STEP_PIN, LOW);
//     OCR3A += radialSteps; 
//     radialSteps += 1;
//   }
//   else{
//     TCCR3B &= (0<<CS10)|(0<<CS11)|(0 << CS12); //turn off Timer3 to stop motor stepping
//     StepperHandler::isCommandActive = false; //sets is command active flag to false
//   }

// begins radial command for stepper
// void StepperHandler::beginRadialCommand(long timerCount, long stepGoal){
//   radialStepGoal = stepGoal; //set radial stepgoal
//   TCCR3A = 0;           // Init Timer3
//   TCCR3B = 0;           // Init Timer3
//   TCCR3B |= (1 << CS10); //set Timer3 prescalar to 1
//   OCR3A = timerCount;        // Timer3 CompareA Register set  
//   TIMSK3 |= (1 << OCIE1A);  // Enable Timer3 COMPA Interrupt
// }


//ISR for radial stepper movement
// ISR(TIMER3_COMPA_vect){
//   if(radialSteps<radialStepGoal){
//     digitalWrite(RADIAL_STEP_PIN, HIGH);
//     digitalWrite(RADIAL_STEP_PIN, LOW);
//     OCR3A += radialSteps; 
//     radialSteps += 1;
//   }
//   else{
//     TCCR3B &= (0<<CS10)|(0<<CS11)|(0 << CS12); //turn off Timer3 to stop motor stepping
//     StepperHandler::isCommandActive = false; //sets is command active flag to false
//   }


