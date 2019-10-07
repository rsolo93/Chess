#include <Stepper.h>

const int stepsPerSquare = 100;
const int STEP1 = 2;
const int DIR1 = 3;
const int STEP2 = 4;
const int DIR2 = 5;
int stepCount = 0;
Stepper myStepper1(stepsPerSquare, 2, 3);
Stepper myStepper2(stepsPerSquare, 4, 5);

void setup() {
  Serial.begin(9600);
  myStepper1.setSpeed(600);
  myStepper2.setSpeed(600);
  
  // put your setup code here, to run once:

}

void loop() {
  for(int i =0 ; i < 5; i++){
  myStepper1.step(stepsPerSquare);
  myStepper2.step(stepsPerSquare);
  Serial.print("steps:");
  Serial.println(stepCount);
  stepCount++;}
  delay(500);
  for(int i = 0; i <5; i++){
  myStepper1.step(-stepsPerSquare);
  myStepper2.step(-stepsPerSquare);}
  delay(500);
  // put your main code here, to run repeatedly:

}
