#include "Chess.h"
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
int step_360 = 211;
int push = 0;
int distance_cm1;
int distance_cm2;
int lastbuttonState = 1;
int lastbuttonState2 =1;
int buttonState;
int buttonState2;

SharpIR mySensor1 = SharpIR(IRPin1, 1080);
//SharpIR mySensor2 = SharpIR(IRPin2, 1080);


void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(xpos, INPUT_PULLUP);
  pinMode(xneg, INPUT);
  pinMode(ypos, INPUT);
  pinMode(yneg, INPUT);
  pinMode(pushBtn, INPUT);
  pinMode(magnet, OUTPUT);
  myStepperX.setSpeed(800);
  myStepperY.setSpeed(800);

}
void loop() {

  distance_cm1 = mySensor1.distance();
//  distance_cm2 = mySensor2.getDistance();
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);

/*  if(digitalRead(pushButton == HIGH){
    digitalWrite(magnet,HIGH);
  }not
  else{
    digitalWrite(magnet,LOW);
  }*/

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

  */
  buttonState = (digitalRead(xpos));
  buttonState2 = (digitalRead(xneg));

  
  if(lastbuttonState != buttonState){
    if(buttonState == LOW){
      moveX(4);
      moveY(4);
//  myStepperX.step(9474);
  //myStepperY.step(-7204);
  }
  lastbuttonState = buttonState;
  }

   if(lastbuttonState2 != buttonState2){
    if(buttonState2 == LOW){
      moveX(4);
      moveY(4);
 // myStepperX.step(-9474);
 // myStepperY.step(7204);
  }

  lastbuttonState2 = buttonState2;
  }

}
