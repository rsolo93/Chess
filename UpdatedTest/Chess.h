#include "LedControl.h"
#include "CTL.h"
#include "SharpIR.h"
#include <stddef.h>
#include <Stepper.h>
int Magbut = 14;
int XposState = 15; 
int XnegState = 16; 
int YposState = 17; 
int YnegState = 18;
int Limit1 = 19;
int Limit2 = 20;
int XState, YState, OldYState, OldXState, OriginX, OriginY, DestinationX, DestinationY, counter;
int a, b, limx, limy, x, y, Case, x1, x2, y1, y2, xmove, ymove, disatnce_cm1, distance_cm2;
//Graveyard variables
int xorig, yorig, xdest, ydest, turn, graveyard, casee;
//SharpIR mySensor1 = SharpIR(A2, 1080);
//SharpIR mySensor2 = SharpIR(A3, 1080);
bool origin = false;
bool destination = false;
const int halfstep = 420;
const int fullstep = halfstep*2;
const int stepsPerRevolution = 211;

LedControl lcW = LedControl(6,8,7,1);//Data, CLK, CS
LedControl lcB = LedControl(9,11,10,2);//Data, CLK, CS
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

    int calc(int x, int y)
    {
        int a = x-y;        
        return a;
    };

int buttonpressW(){
  
  if(digitalRead(XposState) == HIGH){
      XState = XState+1;
      if(XState > 7){XState=0;     
      }
    }
    if(digitalRead(XnegState) == HIGH){
      XState = XState-1;
      if(XState < 0){XState=7;         
      }
    }
    if(digitalRead(YposState) == HIGH){
      YState = YState+1;
      if(YState > 7){YState=0;
      }       
    }
    if(digitalRead(YnegState) == HIGH){
      YState = YState-1;
      if(YState < 0){YState=7;     
      }
    }
    lcW.clearDisplay(0);
    lcW.setLed(0,XState,YState,true);
      delay(120);

    if(XState != OldXState || YState != OldYState){
      lcW.setLed(0,XState,YState,false);
      int OldXState = XState;
      int OldYState = YState;
    }
}

int buttonpressB(){
  
  if(digitalRead(XposState) == HIGH){
      XState = XState+1;
      if(XState > 7){XState=0;     
      }
    }
    if(digitalRead(XnegState) == HIGH){
      XState = XState-1;
      if(XState < 0){XState=7;         
      }
    }
    if(digitalRead(YposState) == HIGH){
      YState = YState+1;
      if(YState > 7){YState=0;
      }       
    }
    if(digitalRead(YnegState) == HIGH){
      YState = YState-1;
      if(YState < 0){YState=7;     
      }
    }
    lcB.clearDisplay(0);
    lcB.setLed(0,XState,YState,true);
      delay(120);

    if(XState != OldXState || YState != OldYState){
      lcB.setLed(0,XState,YState,false);
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
    
    while(digitalRead(Limit1) != LOW)
    moveY(-1);
    while(digitalRead(Limit2) != LOW)
    moveX(1);

    if(digitalRead(Limit1) == LOW && digitalRead(Limit2) == LOW)
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

int Origin(){
  origin == true;
  destination == false;
int MagState = digitalRead(Magbut);

    if(MagState == HIGH && origin == true) {
     x = board_move[XState][YState][0];
     y = board_move[XState][YState][1];
    return x, y;
    }
}

int Destination(){
  origin == false;
  destination == true;
  int MagState = digitalRead(Magbut);

    if(MagState == HIGH && destination == true) {
     a = board_move[XState][YState][0];
     b = board_move[XState][YState][1];
    return a, b;
    }
}
