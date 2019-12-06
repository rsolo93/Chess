#include "Chess.h"
#include "CTL.h"


void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(Magnet, OUTPUT);         //Magnet
  pinMode(Select, INPUT_PULLUP);    //Select
  pinMode(XposState, INPUT_PULLUP);    //Xpos
  pinMode(XnegState, INPUT_PULLUP);    //Yneg
  pinMode(YposState, INPUT_PULLUP);    //Ypos
  pinMode(YnegState, INPUT_PULLUP);    //Yneg
  pinMode(LimitY, INPUT); //Limitswitch 1
  pinMode(LimitX, INPUT); //Limitswitch 2
  pinMode(wait, OUTPUT);
  pinMode(tg, OUTPUT);
  pinMode(ty, OUTPUT);
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  lcd1.begin(16,2);
  lcd2.begin(16,2);
  digitalWrite(Magnet,HIGH);
  myStepperX.setSpeed(500);
  myStepperY.setSpeed(500);
  homing();
  lcd1.clear();
  lcd2.clear();
 
}

  void loop() {
  distance_cm1 = mySensor1.distance();
  distance_cm2 = mySensor2.distance();
  Case = 1;

  while (distance_cm1 > 15 || distance_cm2 > 15){
    distance_cm1 = mySensor1.distance();
    distance_cm2 = mySensor2.distance();
    Serial.print("Mean distance1: ");
    Serial.print(distance_cm1);
    Serial.println(" cm");
    Serial.print("Mean distance2: ");
    Serial.print(distance_cm2);
    Serial.println(" cm");
    lcd1.clear(); 
    lcd2.clear();
    lcd1.print("Step Up");
    lcd2.print("Step up");
    delay(500);
  }

  switch(Case){
    case 1:
      lcd1.clear();
      lcd2.clear();
      digitalWrite(ty,HIGH);
      digitalWrite(tg,LOW);
      Serial.println("Choose Origin");
      lcd1.setCursor(0,0);
      lcd1.print("Choose Origin ");
      lcd1.setCursor(0,1);
      lcd1.print("Position: ");
      lcd2.print("Waiting For ");
      lcd2.setCursor(1,2);
      lcd2.print("Opponent");
      lcd1.noAutoscroll();
      lcd2.noAutoscroll();
        while(1){
          buttonpress();
          x1 = XState;
          y1 = YState;
          DisplayMoveYellowOrigin(x1, y1);
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
        digitalWrite(ty,HIGH);
        digitalWrite(tg,LOW);
        lcd1.clear();
        lcd1.clear();
        lcd1.setCursor(0,0);
        lcd1.print("Destination ");
        lcd1.setCursor(0,1);
        lcd1.print("Position: ");
        lcd2.print("Waiting For ");
        lcd2.setCursor(1,2);
        lcd2.print("Opponent");
        lcd1.noAutoscroll();
        lcd2.noAutoscroll();

        while(1){
          buttonpress();
          x2 = XState;
          y2 = YState;
          DisplayMoveYellowDestination(x2, y2);
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
      digitalWrite(ty,HIGH);
      digitalWrite(tg,LOW);
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
      
    }
    
    case 4:  // KSU TURN
       Serial.println("Initiate Moving Piece");
       digitalWrite(ty,HIGH);
       digitalWrite(tg,LOW);
       digitalWrite(wait, HIGH);
       lcd1.clear();
       lcd2.clear();
       lcd1.print(phrase[random(0,3)]);
       lcd1.setCursor(0,2);
       lcd1.print("In Progress");
       lcd2.print("Waiting For ");
       lcd2.setCursor(1,2);
       lcd2.print("Opponent");
       lcd1.noAutoscroll();
       lcd2.noAutoscroll();
       while(1){
         moveX(940);
         delay(2000);
         moveX((OriginX+1)*840);
         moveY((OriginY+2)*840);
         moveX(-420);
         moveY(-420);
         digitalWrite(Magnet,LOW);
         delay(1000);
         Orig2Dest();
         moveX(520);
         moveY(420);
         delay(2000);
         Serial.print("ymove is ");
         Serial.println(ymove);
         moveY(-(ymove)*840);
         Serial.print("xmove is ");
         Serial.print(xmove);
         Serial.print(" ");
         moveX(-xmove*840);
         delay(1000);
         moveX(-420);
         moveY(-520);
         digitalWrite(Magnet,HIGH);
         delay(1000);
         Serial.println("Done");
         homing();
         digitalWrite(wait, LOW);
         break;
       }
         
        

      case 5:

      Serial.println("Choose Origin2");
      digitalWrite(ty,LOW);
      digitalWrite(tg,HIGH);
      lcd1.clear();
      lcd2.clear();
      Serial.println("Choose Origin");
      lcd2.setCursor(0,0);
      lcd2.print("Choose Origin ");
      lcd2.setCursor(0,1);
      lcd2.print("Position: ");
      lcd1.print("Waiting For ");
      lcd1.setCursor(1,2);
      lcd1.print("Opponent");
      lcd1.noAutoscroll();
      lcd2.noAutoscroll();
        while(1){
          buttonpress();
          x1 = XState;
          y1 = YState;
          DisplayMoveGreenOrigin(x1, y1);
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
        digitalWrite(ty,LOW);
        digitalWrite(tg,HIGH);
        lcd1.clear();
        lcd2.clear();
        lcd2.setCursor(0,0);
        lcd2.print("Destination ");
        lcd2.setCursor(0,1);
        lcd2.print("Position: ");
        lcd1.print("Waiting For ");
        lcd1.setCursor(1,2);
        lcd1.print("Opponent");
        lcd1.noAutoscroll();
        lcd2.noAutoscroll();

        while(1){
          buttonpress();
          x2 = XState;
          y2 = YState;
          DisplayMoveGreenDestination(x2, y2);
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
      digitalWrite(ty,LOW);
      digitalWrite(tg,HIGH);
      xorig = OriginX;
      yorig = OriginY;
      xdest = DestinationX;
      ydest = DestinationY;
      turn = 1;
      int arr[2] = {0,0};
      CTL(xorig,yorig,xdest,ydest,turn,graveyard,arr);
      delay(1000);
      casee = arr[0];
      graveyard = arr[1];
      Serial.print("graveyard spot ");
      Serial.print(graveyard);
      Serial.print("   ");
      Serial.print("casee ");
      Serial.print(casee);
      Serial.print('\n');
      }
      
    

      case 8:  // SPSU TURN

      Serial.println("Initiate Moving Piece");
      digitalWrite(ty,LOW);
      digitalWrite(tg,HIGH);
      digitalWrite(wait, HIGH); 
       lcd1.clear();
       lcd2.clear();
       lcd2.print(phrase[random(0,3)]);
       lcd2.setCursor(0,2);
       lcd2.print("In Progress");
       lcd1.print("Waiting For ");
       lcd1.setCursor(1,2);
       lcd1.print("Opponent");
       lcd1.noAutoscroll();
       lcd2.noAutoscroll();
       moveX(940);
       moveX((OriginX+1)*840);
       moveY((OriginY+1)*840);
       moveX(-520);
       moveY(-420);
       digitalWrite(Magnet,LOW);
       delay(1000);
       moveX(720);
       moveY(420);
       Orig2Dest();
       delay(1000);
       Serial.print("ymove is ");
       Serial.println(ymove);
       moveY(-ymove*840);
       Serial.print("xmove is ");
       Serial.print(xmove);
       Serial.print(" ");
       moveX(-xmove*840);
       delay(1000);
       moveX(-720);
       moveY(420);
       digitalWrite(Magnet,HIGH);
       delay(1000);
      Serial.println("Done");
      homing();
      digitalWrite(wait, LOW);
      break;    
        }
  } 
      



  
