#include "Chess.h"
#include "SharpIR.h"
#include "MCP23017.h"
#define IRPin1 A2
#define IRPin2 A3


//#define pushbutton A3
//#define magnet 6
const int magnet = 6;
const int pushBtn = 13;
int xPosition = 0;
int yPosition = 0;
int dist = 0;
int mapX = 0;
int mapY = 0;
int step_360 = 211;
int push = 0;
int xmove, ymove;
int distance_cm1;
int distance_cm2;
int lastbuttonState = 1;
int lastbuttonState2 =1;
int buttonState;
int buttonState2;
int cas = 1;
int Case,x1,x2,y1,y2;

//SharpIR mySensor1 = SharpIR(IRPin1, 1080);
//SharpIR mySensor2 = SharpIR(IRPin2, 1080);


void setup() {
  // initialize the serial port:
  Serial.begin(9600);
/*  pinMode(Magbut, INPUT_PULLUP);
  pinMode(Xpos, INPUT_PULLUP);
  pinMode(Xneg, INPUT_PULLUP);
  pinMode(Ypos, INPUT_PULLUP);
  pinMode(Yneg, INPUT_PULLUP);
  pinMode(pushBtn, INPUT);*/
  pinMode(magnet, OUTPUT);
  mcp.begin(7);
  
  mcp.pinMode(0, INPUT_PULLUP);    //Magbut
  mcp.pinMode(1, INPUT_PULLUP);    //Xpos
  mcp.pinMode(2, INPUT_PULLUP);    //Yneg
  mcp.pinMode(3, INPUT_PULLUP);    //Ypos
  mcp.pinMode(4, INPUT_PULLUP);    //Yneg
  mcp.pinMode(5, INPUT); //Limitswitch 1
  mcp.pinMode(6, INPUT); //Limitswitch 2
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  myStepperX.setSpeed(800);
  myStepperY.setSpeed(800);
  homing();

}
  void loop() {
  int switchCase =mcp.digitalRead(0);
  Case = 0;
  if(switchCase == HIGH){
      Case = Case+1;
    //  Serial.print(Case);
      if(Case > 6){Case=0;     
      }

  switch(Case){
    case 1:
      Serial.println("Choose Origin");
        while(1){
          buttonpress();
          x1 = XState;
          y1 = YState;
          int swit =  mcp.digitalRead(0);
          if(swit == HIGH){
            OriginX = board_move[XState][YState][0];
            OriginY = board_move[XState][YState][1];
            Serial.print(" Origin Coordinates are: ");
            Serial.print(OriginX);
            Serial.print(" | ");
            Serial.println(OriginY);
            delay(1000);
           break;
           XState = 0;
           YState = 0;
          }
      }
    case 2:
      Serial.println("Choose Destination");
        while(1){
          buttonpress();
          x2 = XState;
          y2 = YState;
          int swit =  mcp.digitalRead(0);
          if(swit == HIGH){
          DestinationX = board_move[XState][YState][0];
          DestinationY = board_move[XState][YState][1];
            Serial.print("Destination Coordinates are: ");
            Serial.print(DestinationX);
            Serial.print(" | ");
            Serial.println(DestinationY);
           XState = 0;
           YState = 0;
           break;
          }
        }
    case 3:
       Serial.println("Initiate Moving Piece");
       moveX(-(OriginX+1)*840);
       moveY((OriginY+1)*840);
       
       if(OriginX > DestinationX)
       xmove = abs((DestinationX-OriginX));
       else
       xmove = -abs(DestinationX-OriginX);

       if(OriginY > DestinationY)
       ymove = abs(DestinationY-OriginY);
       else
       ymove = -abs(DestinationY-OriginY);
       
       Serial.print("xmove is ");
       Serial.print(xmove);
       Serial.print(" ");
       moveX(xmove*840);
       Serial.print("ymove is ");
       Serial.println(ymove);
       moveY(-ymove*840);
      Serial.println("Done");
      delay(2000);
      homing();
      break;    
      /*
    case 4:
      Serial.print("Initiate");
        while(switchCase == HIGH){
          moveX((x2-x1)*840-420);
          moveY((y2-y1)*840-420);

          delay(5000);
      }
      break;*/
  }
  }

}

  
 /* buttonpress();
  Origin();
  OriginX = x;
  OriginY = y;
  Serial.print("OriginX: ");
  Serial.print(OriginX);
  Serial.print(" | OriginY: ");
  Serial.println(OriginY);
  Destination();
  DestinationX = a;
  DestinationY = b;
  Serial.print("DestinationX: ");
  Serial.print(DestinationX);
  Serial.print(" | DestinationY: ");
  Serial.print(DestinationY);
  Serial.println("   "); 
  //moveX((DestinationX-OriginX)*840);
  //moveY((DestinationY-DestinationX)*840);
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
