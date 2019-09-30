
/*
 Stepper Motor Control - one step at a time

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor will step one step at a time, very slowly.  You can use this to
 test that you've got the four wires of your stepper wired to the correct
 pins. If wired correctly, all steps should be in the same direction.

 Use this also to count the number of steps per revolution of your motor,
 if you don't know it.  Then plug that number into the oneRevolution
 example to see if you got it right.

 Created 30 Nov. 2009
 by Tom Igoe

 */
#define xPin A0
#define yPin A1
int xPosition = 0;
int yPosition = 0;
int mapX = 0;
int mapY = 0;
int moveY = 0;
int moveX = 0;
int step_360 = 211;
#include <Stepper.h>


const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepperY(stepsPerRevolution, 2,3);
Stepper myStepperX(stepsPerRevolution, 4,5);

int stepCount = 0;         // number of steps the motor has taken

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  myStepperX.setSpeed(600);
  myStepperY.setSpeed(600);

}

void loop() {

  xPosition = analogRead(xPin);
  yPosition = analogRead(yPin);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);

  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.println();
 /* if(mapY > 0)
  moveY = stepsPerRevolution;
  else
  moveY = -stepsPerRevolution;
  if(mapX > 0)
  moveX = -stepsPerRevolution;
  else
  moveX = stepsPerRevolution;*/

  if(mapX > 50 && mapY >50){
    for(int s=0; s<step_360; s++)
{
 myStepperX.step(-1);
 myStepperY.step(1);
}

  }
  if(mapX < -10 && mapY < -10){
    for(int s=0; s<step_360; s++)
{
 myStepperX.step(1);
 myStepperY.step(-1);
}
  }
  
  if(mapX < -10 && mapY > 50){
    for(int s=0; s<step_360; s++)
{
 myStepperX.step(1);
 myStepperY.step(1);
}
  }

  if(mapX > 50 && mapY < -10){
    for(int s=0; s<step_360; s++)
{
 myStepperX.step(-1);
 myStepperY.step(-1);
}
    
  }

  if(mapX >50 && (mapY > -10 && mapY < 50))
  for(int s=0; s<step_360; s++)
    myStepperX.step(-1);
  if(mapX <-10 && (mapY > -10 && mapY < 50))
  for(int s=0; s<step_360; s++)
  myStepperX.step(1);
  if(mapY >50 && (mapX > -10 && mapX < 50))
  for(int s=0; s<step_360; s++)
  myStepperY.step(1);
  if(mapY <-10 && (mapX > -10 && mapX < 50))
  for(int s=0; s<step_360; s++)
  myStepperY.step(-1);
  
//  myStepperY.step(moveY)


  //tepperX.step(moveX);


  //delay(500);
/*
  Serial.println("CounterClockwise");
  for(int i=0; i<5; i++){
  myStepper.step(-stepsPerRevolution*i);
  i = rand()*5;
    delay(500);} */
 //delay(500);

  
}
