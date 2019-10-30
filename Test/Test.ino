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
  pinMode(Magbut, INPUT);
  pinMode(Xpos, INPUT_PULLUP);
  pinMode(Xneg, INPUT_PULLUP);
  pinMode(Ypos, INPUT_PULLUP);
  pinMode(Yneg, INPUT_PULLUP);
  pinMode(pushBtn, INPUT);
  pinMode(magnet, OUTPUT);
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  myStepperX.setSpeed(800);
  myStepperY.setSpeed(800);

}
void loop() {

  distance_cm1 = mySensor1.distance();
//  distance_cm2 = mySensor2.getDistance();

  buttonpress();
  movePiece();
  /*
  Serial.print(XmoveO);
  Serial.print(" | ");
  Serial.print(YmoveO);
  Serial.print(" | | ");
  Serial.print(XmoveD);
  Serial.print(" | ");
  Serial.print(YmoveD);
  Serial.println();
*/
  

/*  if(digitalRead(pushButton == HIGH){
    digitalWrite(magnet,HIGH);
  }not
  else{
    digitalWrite(magnet,LOW);
  }*/

 /* Serial.print("X: ");
  Serial.print(digitalRead(xpos));
  Serial.print(" | Y: ");
  Serial.print(digitalRead(ypos));
 // Serial.print(" | Distance: ");
 // Serial.print(dist);
  //Serial.println();*/
 /* Serial.print(" | push: ");
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



}
