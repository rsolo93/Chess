#define xPin A0
#define yPin A1
#define IRPin1 A2
#define IRPin2 A3
int xPosition = 0;
int yPosition = 0;
int dist = 0;
int mapX = 0;
int mapY = 0;
int moveY = 0;
int moveX = 0;
int step_360 = 211;
int distance_cm1;
int distance_cm2;
#include <Stepper.h>
#include <SharpIR.h>


const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 2 through 5:
Stepper myStepperY(stepsPerRevolution, 2,3);
Stepper myStepperX(stepsPerRevolution, 4,5);
SharpIR mySensor1 = SharpIR(IRPin1, 1080);
SharpIR mySensor2 = SharpIR(IRPin2, 1080);

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

  distance_cm1 = mySensor1.distance();
  distance_cm2 = mySensor2.distance();
  Serial.print("Mean distance 1: ");
  Serial.print(distance_cm1);
  Serial.println(" cm");
  Serial.print("Mean distance 2: ");
  Serial.print(distance_cm2);
  Serial.println(" cm");
//  delay(400);
  
  xPosition = analogRead(xPin);
  yPosition = analogRead(yPin);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);

    //delay(500);
    if(distance_cm1 > 35){
      for(int s=0; s<step_360; s++)
      {
        myStepperY.step(-1);
      }
    }
    if(distance_cm1 < 15){
      for(int s=0; s<step_360; s++)
      {
        myStepperY.step(1);
      }
    }
    
  


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
}
