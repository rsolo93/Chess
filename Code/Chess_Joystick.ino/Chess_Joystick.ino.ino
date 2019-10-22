
#include <Stepper.h>


#define xPin A0
#define yPin A1
#define sens A2
//#define pushbutton A3
//#define magnet 6
const int pushbutton =10;
const int magnet = 6;
int xPosition = 0;
int yPosition = 0;
int dist = 0;
int mapX = 0;
int mapY = 0;
int moveY = 0;
int moveX = 0;
int step_360 = 211;
int push = 0;

int stepsPerRevolution = 211;
// initialize the stepper library on pins 8 through 11:
Stepper myStepperX(stepsPerRevolution, 2,3);
Stepper myStepperY(stepsPerRevolution, 4,5);


void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(sens, INPUT);
  pinMode(magnet, OUTPUT);
  pinMode(pushbutton, INPUT_PULLUP);
  //digitalWrite(pushbutton, HIGH);
  myStepperX.setSpeed(600);
  myStepperY.setSpeed(600);

}

void loop() {

  xPosition = analogRead(xPin);
  yPosition = analogRead(yPin);
  push = digitalRead(pushbutton);
 // dist = analogRead(sens);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);

  if(push == LOW){
    digitalWrite(magnet,HIGH);
  }
  else{
    digitalWrite(magnet,LOW);
  }
    
  /*Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
 // Serial.print(" | Distance: ");
 // Serial.print(dist);
  //Serial.println();*/
  Serial.print(" | push: ");
  Serial.print(push);
  Serial.println();


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
    
  }

  if(mapX >50 && (mapY > -50 && mapY < 50))
  for(int s=0; s<step_360; s++)
    myStepperX.step(1);
  if(mapX <-50 && (mapY > -50 && mapY < 50))
  for(int s=0; s<step_360; s++)
  myStepperX.step(-1);
  if(mapY >50 && (mapX > -50 && mapX < 50))
  for(int s=0; s<step_360; s++)
  myStepperY.step(-1);
  if(mapY <-50 && (mapX > -50 && mapX < 50))
  for(int s=0; s<step_360; s++)
  myStepperY.step(1);


  
}
