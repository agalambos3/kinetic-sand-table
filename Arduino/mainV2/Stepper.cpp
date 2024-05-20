#include "Arduino.h"
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
    radialDriver.TCOOLTHRS(0xFFFFF); //better stallguard at low speed this way?
    
    commandDone = false;

    return 1;
}

// begins specified command 
void StepperHandler::beginCommand(stepCommand* ptr){
    activeCommand = *ptr;
    //set radial stepper direction
    if(activeCommand.radialStepGoal>0){
      digitalWrite(RADIAL_DIR_PIN, HIGH);
    }
    else{
      digitalWrite(RADIAL_DIR_PIN, LOW);
    }
    //set angular stepper direction
    if(activeCommand.angularStepGoal>0){
      digitalWrite(ANGULAR_DIR_PIN, HIGH);
    }
    else{
      digitalWrite(ANGULAR_DIR_PIN, LOW);
    }
    radialSteps = 0;
    angularSteps = 0;
    radialDone = false;
    angularDone = false;
    commandDone = false;
    //setup radial timer 
    TCCR3A = 0;           // Init Timer3
    TCCR3B = 0;           // Init Timer3
    TCCR3B |= (1 << CS10); //set Timer3 prescalar to 1
    OCR3A = activeCommand.radialTimerCount;   // Timer3 CompareA Register
    TIMSK3 |= (1 << OCIE1A);  // Enable Timer3 COMPA Interrupt
    
    //setup angular timer 
    TCCR1A = 0; // Init Timer1
    TCCR1B = 0; // Init Timer1
    TCCR1B |= (1 << CS10); //set Timer1 prescalar to 1
    OCR1A = activeCommand.angularTimerCount; //Timer1 CompareA Register
    TIMSK1 |= (1 << OCIE1A); //  Enable Timer1 COMPA Interrupt    
}

//ISR for radial stepper movement
void StepperHandler::radialStepISR(){
  if(radialSteps<abs(activeCommand.radialStepGoal)){
    digitalWrite(RADIAL_STEP_PIN, HIGH);
    digitalWrite(RADIAL_STEP_PIN, LOW);
    OCR3A += activeCommand.radialTimerCount; 
    radialSteps += 1;

  }
  else {
    radialDone = true;
    TIMSK3 &= (0 << OCIE1A);
    TCCR3B &= (0<<CS10)|(0<<CS11)|(0 << CS12); //turn off Timer3 to stop motor stepping   
    if ((radialDone && angularDone) == true) {
      commandDone = true;    
    }
  }
}

//ISR for angular stepper movement
void StepperHandler::angularStepISR(){
  if(angularSteps<abs(activeCommand.angularStepGoal)){
    digitalWrite(ANGULAR_STEP_PIN, HIGH);
    digitalWrite(ANGULAR_STEP_PIN, LOW);
    OCR1A += activeCommand.angularTimerCount; 
    angularSteps += 1;
  }
  else {
    angularDone = true;
    TIMSK1 &= (0 << OCIE1A);
    TCCR1B &= (0<<CS10)|(0<<CS11)|(0 << CS12); //turn off Timer1 to stop motor stepping
    if ((radialDone && angularDone) == true) {
      commandDone = true;
    }
  }
}

void StepperHandler::stallISR(){
  if(sinceStall > MIN_STALL_TIME){
    TCCR3B &= (0<<CS10)|(0<<CS11)|(0 << CS12); //turn off Timer3 to stop radial stepping
    TCCR1B &= (0<<CS10)|(0<<CS11)|(0 << CS12); //turn off Timer1 to stop angular stepping
    sinceStall = 0; //time since stall set to zero
  }
}

bool StepperHandler::isCommandDone(){
  return commandDone;
}
