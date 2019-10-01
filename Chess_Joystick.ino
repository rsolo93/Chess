
 
#define xPin A0
#define yPin A1
#define sens A2
//#define sens 9
int xPosition = 0;
int yPosition = 0;
int dist = 0;
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
  pinMode(sens, INPUT);
  myStepperX.setSpeed(600);
  myStepperY.setSpeed(600);

}

void loop() {

  xPosition = analogRead(xPin);
  yPosition = analogRead(yPin);
  dist = analogRead(sens);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);

  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print(" | Distance: ");
  Serial.print(dist);
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
