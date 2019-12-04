#include "Chess.h"
#include "CTL.h"


void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(Select, INPUT_PULLUP);    //Select
  pinMode(XposState, INPUT_PULLUP);    //Xpos
  pinMode(XnegState, INPUT_PULLUP);    //Yneg
  pinMode(YposState, INPUT_PULLUP);    //Ypos
  pinMode(YnegState, INPUT_PULLUP);    //Yneg
  pinMode(LimitY, INPUT); //Limitswitch 1
  pinMode(LimitX, INPUT); //Limitswitch 2
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  lcd1.begin(16,2);
  //lcd2.begin(16,2);
  myStepperX.setSpeed(800);
  myStepperY.setSpeed(800);
  homing();
  Serial.println(digitalRead(LimitY));
  Serial.println(digitalRead(LimitX));

  

}
  void loop() {
  //int switchCase = digitalRead(Select);
  distance_cm1 = mySensor1.distance();
  distance_cm2 = mySensor2.distance();
/*  if(distance_cm1 > 50){
    lcd1.print("Welcome Player 1");
  }
  if(distance_cm2 > 50){
    lcd2.print("Welcome Player 2");
  }*/
  Case = 1;
  /*if(switchCase == HIGH){
      Case = Case+1;
      Serial.print(Case);
      if(Case > 6){Case=0;     
      }*/

  switch(Case){
    case 1:
      Serial.println("Choose Origin");
      lcd1.clear(); 
      lcd1.print("Player 1 Choose Origin");
      delay(3000);
        while(1){
          buttonpress();
          x1 = XState;
          y1 = YState;
          int swit =  digitalRead(Select);
          if(swit == LOW){
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
      lcd1.clear();
      lcd1.print("Player 1 Choose Destination");

        while(1){
          buttonpress();
          x2 = XState;
          y2 = YState;
          int swit = digitalRead(Select);
          if(swit == LOW){
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
    {
      xorig = OriginX;
      yorig = OriginY;
      xdest = DestinationX;
      ydest = DestinationY;
      turn = 0;
      graveyard,casee = 0;
      int arr[2] = {0,0};
      CTL(xorig,yorig,xdest,ydest,turn,graveyard,arr);
      delay(2000);
      casee = arr[0];
      graveyard = arr[1];
      Serial.print("graveyard spot ");
      Serial.print(graveyard);
      Serial.print("   ");
      Serial.print("casee ");
      Serial.print(casee);
      Serial.print('\n');
      Case = casee;
      switch (Case){
        case 1:
        Case = 1;
        break;
        case 4:
        Case = 4;
        break;
      }
      
    }
    
    case 4:
       Serial.println("Initiate Moving Piece");
       lcd1.clear();
       lcd1.print("Great Move In Progress");

       while(1){
         moveX(-(OriginX+1)*840);
         moveY((OriginY+1)*840);
         Orig2Dest();
         delay(2000);
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
       }
         
        

      case 5:

      Serial.println("Choose Origin2");
        while(1){
          buttonpress();
          x1 = XState;
          y1 = YState;
          int swit =  digitalRead(Select);
          if(swit == LOW){
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

      case 6:

      Serial.println("Choose Destination");
        while(1){
          buttonpress();
          x2 = XState;
          y2 = YState;
          int swit = digitalRead(Select);
          if(swit == LOW){
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

      case 7:

        {
      xorig = OriginX;
      yorig = OriginY;
      xdest = DestinationX;
      ydest = DestinationY;
      turn = 1;
      int arr[2] = {0,0};
      CTL(xorig,yorig,xdest,ydest,turn,graveyard,arr);
      delay(2000);
      casee = arr[0];
      graveyard = arr[1];
      Serial.print("graveyard spot ");
      Serial.print(graveyard);
      Serial.print("   ");
      Serial.print("casee ");
      Serial.print(casee);
      Serial.print('\n');
      Case = casee;
      switch (Case){
        case 1:
        Case = 5;
        break;
        case 8:
        Case = 8;
        break;
      }
      
    }

      case 8:

      Serial.println("Initiate Moving Piece");
       moveX(-(OriginX+1)*840);
       moveY((OriginY+1)*840);
       
       Orig2Dest();
       delay(2000);
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
        }
  } 
      



  
