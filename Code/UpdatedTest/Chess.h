#include "LedControl.h"
#include "SharpIR.h"
#include <stddef.h>
#include <Stepper.h>
#include <LiquidCrystal.h>
int Select = 52;
int YposState = 32; 
int YnegState = 30; 
int XnegState = 28; 
int XposState = 24 ;
int LimitY = 19;
int LimitX = 20;
int Magnet = 50;
int XState, YState, OldYState, OldXState, OriginX, OriginY, DestinationX, DestinationY, counter;
int a, b, limx, limy, x, y, Case, x1, x2, y1, y2, xmove, ymove, distance_cm1, distance_cm2;
//Graveyard variables
int xorig, yorig, xdest, ydest, turn, graveyard, casee;
SharpIR mySensor1 = SharpIR(A2, 1080);
SharpIR mySensor2 = SharpIR(A3, 1080);
const int halfstep = 420;
const int fullstep = halfstep*2;
const int stepsPerRevolution = 211;

LiquidCrystal lcd1(6, 9, 7, 8, 12, 13); //displayYellow (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd2(10, 11, 17, 16, 15, 14); //displayGreen (rs, enable, d4, d5, d6, d7)
LedControl lc = LedControl(6,8,7,1);//Data, CLK, CS
Stepper myStepperX(stepsPerRevolution, 2,3); //top down
Stepper myStepperY(stepsPerRevolution, 4,5); //top down

    const int board_move[8][8][2] =
    {
      
    //Capital Letters are WHITE
      { {0,0},  {1,0},  {2,0},  {3,0},  {4,0},  {5,0},  {6,0},  {7,0}  },
      { {0,1},  {1,1},  {2,1},  {3,1},  {4,1},  {5,1},  {6,1},  {7,1}  },
      { {0,2},  {1,2},  {2,2},  {3,2},  {4,2},  {5,2},  {6,2},  {7,2}  },
      { {0,3},  {1,3},  {2,3},  {3,3},  {4,3},  {5,3},  {6,3},  {7,3}  },
      { {0,4},  {1,4},  {2,4},  {3,4},  {4,4},  {5,4},  {6,4},  {7,4}  },
      { {0,5},  {1,5},  {2,5},  {3,5},  {4,5},  {5,5},  {6,5},  {7,5}  },
      { {0,6},  {1,6},  {2,6},  {3,6},  {4,6},  {5,6},  {6,6},  {7,6}  },
      { {0,7},  {1,7},  {2,7},  {3,7},  {4,7},  {5,7},  {6,7},  {7,7}  },
    };

      
    const char *Display [8][8] =
    {

      {"A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1"},
      {"A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2"},
      {"A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3"},
      {"A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4"},
      {"A5", "B5", "C5", "D5", "E5", "F5", "G5", "H5"},
      {"A6", "B6", "C6", "D6", "E6", "F6", "G6", "H6"},
      {"A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7"},
      {"A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8"}
    };



int buttonpress(){
  
  if(digitalRead(XposState) == LOW){
      XState = XState+1;
      if(XState > 7){XState=0;     
      }
    }
    if(digitalRead(XnegState) == LOW){
      XState = XState-1;
      if(XState < 0){XState=7;         
      }
    }
    if(digitalRead(YposState) == LOW){
      YState = YState+1;
      if(YState > 7){YState=0;
      }       
    }
    if(digitalRead(YnegState) == LOW){
      YState = YState-1;
      if(YState < 0){YState=7;     
      }
    }
    lc.clearDisplay(0);
    lc.setLed(0,XState,YState,true);
      delay(120);

    if(XState != OldXState || YState != OldYState){
      lc.setLed(0,XState,YState,false);
      int OldXState = XState;
      int OldYState = YState;
    }
}


    void moveX(int mx)
    {
        myStepperX.step(mx);
    };

    void moveY(int my)
    {
        myStepperY.step(-my);
    };


  void homing(){
    
    while(digitalRead(LimitY) != LOW)
    moveY(-1);
    while(digitalRead(LimitX) != LOW)
    moveX(1);

    if(digitalRead(LimitY) == LOW && digitalRead(LimitX) == LOW)
    return;
  };

  void Orig2Dest(){
    if(OriginX > DestinationX)
       xmove = abs((DestinationX-OriginX));
       else
       xmove = -abs(DestinationX-OriginX);

       if(OriginY > DestinationY)
       ymove = abs(DestinationY-OriginY);
       else
       ymove = -abs(DestinationY-OriginY);
    return;
  };



int Graveyard(int xGet,int yGet,int xGrave,int yGrave){
  moveX(-(xGet+1)*840);
  moveY((yGet+1)*840);
  moveX(-420);
  moveY(420);
  digitalWrite(Magnet, LOW);
  delay(2000);
  moveX(420);
  moveY(-420);
  moveX((xGet+1-xGrave)*840);
  moveY(-(yGet+1-yGrave)*840);
  digitalWrite(Magnet,HIGH);
  homing();
  
}

int DisplayMoveYellowOrigin(int x, int y){
  lcd1.clear();
  lcd1.setCursor(0,0);
  lcd1.print("Choose Origin ");
  lcd1.setCursor(0,1);
  lcd1.print("Position: ");
  lcd1.setCursor(9,1);
  lcd1.print(Display[y][x]);
  lcd2.clear();
  lcd2.clear();
  lcd2.print("Waiting For ");
  lcd2.setCursor(1,2);
  lcd2.print("Opponent");
  lcd1.noAutoscroll();
  lcd2.noAutoscroll();

}

int DisplayMoveYellowDestination(int x, int y){
  lcd1.clear();
  lcd1.setCursor(0,0);
  lcd1.print("Destination ");
  lcd1.setCursor(0,1);
  lcd1.print("Position: ");
  lcd1.setCursor(9,1);
  lcd1.print(Display[y][x]);
  lcd2.clear();
  lcd2.clear();
  lcd2.print("Waiting For ");
  lcd2.setCursor(1,2);
  lcd2.print("Opponent");
  lcd1.noAutoscroll();
  lcd2.noAutoscroll();

}


int DisplayMoveGreenOrigin(int x, int y){
  lcd2.clear();
  lcd2.setCursor(0,0);
  lcd2.print("Choose Origin ");
  lcd2.setCursor(0,1);
  lcd2.print("Position: ");
  lcd2.setCursor(9,1);
  lcd2.print(Display[y][x]);
  lcd1.clear();
  lcd1.print("Waiting For ");
  lcd1.setCursor(1,2);
  lcd1.print("Opponent");
  lcd1.noAutoscroll();
  lcd2.noAutoscroll();

}

int DisplayMoveGreenDestination(int x, int y){
  lcd2.clear();
  lcd2.setCursor(0,0);
  lcd2.print("Destination ");
  lcd2.setCursor(0,1);
  lcd2.print("Position: ");
  lcd2.setCursor(9,1);
  lcd2.print(Display[y][x]);
  lcd1.clear();
  lcd1.print("Waiting For ");
  lcd1.setCursor(1,2);
  lcd1.print("Opponent");
  lcd1.noAutoscroll();
  lcd2.noAutoscroll();

}
