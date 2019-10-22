#include <Stepper.h>
#include "SharpIR.h"

#define IRPin1 A2
#define IRPin2 A3
//#define pushbutton A3
//#define magnet 6
const int magnet = 6;
const int pushBtn = 13;
const int xpos = 12;
const int xneg = 11;
const int ypos = 10;
const int yneg = 9;
int xPosition = 0;
int yPosition = 0;
int dist = 0;
int mapX = 0;
int mapY = 0;
int moveY = 0;
int moveX = 0;
int step_360 = 211;
int push = 0;
int distance_cm1;
int distance_cm2;

int stepsPerRevolution = 211;

Stepper myStepperX(stepsPerRevolution, 2,3);
Stepper myStepperY(stepsPerRevolution, 4,5);
SharpIR mySensor1 = SharpIR(IRPin1, 1080);
//SharpIR mySensor2 = SharpIR(IRPin2, 1080);


void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(xpos, INPUT);
  pinMode(xneg, INPUT);
  pinMode(ypos, INPUT);
  pinMode(yneg, INPUT);
  pinMode(pushBtn, INPUT);
  pinMode(magnet, OUTPUT);
  myStepperX.setSpeed(600);
  myStepperY.setSpeed(600);

}
void loop() {

  distance_cm1 = mySensor1.distance();
//  distance_cm2 = mySensor2.getDistance();
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);

  if(digitalRead(pushBtn) == HIGH){
    digitalWrite(magnet,HIGH);
  }
  else{
    digitalWrite(magnet,LOW);
  }

  Serial.print("X: ");
  Serial.print(digitalRead(xpos));
  Serial.print(" | Y: ");
  Serial.print(digitalRead(ypos));
 // Serial.print(" | Distance: ");
 // Serial.print(dist);
  //Serial.println();*/
  Serial.print(" | push: ");
  Serial.print(push);
  Serial.print(" | Mean distance 1: ");
  Serial.print(distance_cm1);
  Serial.println(" cm");
 /* Serial.print("Mean distance 2: ");
  Serial.print(distance_cm2);
  Serial.println(" cm");*/
  /*
  if(mapX > 50 && mapY >50){
    for(int s=0; s<step_360; s++)
{
 myStepperX.step(1);
 myStepperY.step(-1);
}

  }
  if(mapX < -50 && mapY < -50){
    for(int s=0; s<step_360; s++)
{
 myStepperX.step(-1);
 myStepperY.step(1);
}
  }

  if(mapX < -50 && mapY > 50){
    for(int s=0; s<step_360; s++)
{
 myStepperX.step(-1);
 myStepperY.step(-1);
}
  }

  if(mapX > 50 && mapY < -50){
    for(int s=0; s<step_360; s++)
{
 myStepperX.step(1);
 myStepperY.step(1);
}
*/
   if(digitalRead(xpos) == HIGH && digitalRead(ypos) ==HIGH){
  for(int s=0; s<step_360; s++){
    myStepperX.step(-1);
    myStepperY.step(1);
}}

  if(digitalRead(xpos) == HIGH)
  for(int s=0; s<step_360; s++)
    myStepperX.step(1);
  if(digitalRead(xneg) == HIGH)
  for(int s=0; s<step_360; s++)
  myStepperX.step(-1);
  if(digitalRead(ypos) == HIGH)
  for(int s=0; s<step_360; s++)
  myStepperY.step(-1);
  if(digitalRead(yneg) == HIGH)
  for(int s=0; s<step_360; s++)
  myStepperY.step(1);

  


}
