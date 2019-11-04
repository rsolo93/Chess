#include "LedControl.h"
#include <Stepper.h>
#include <SharpIR.h>
LedControl lc = LedControl(6,7,8,1);
int XState, YState, OldXState, OldYState, Case, OriginX, OriginY, DestinationX, DestinationY;
int Magbut = 13;
int Xpos = 12;
int Xneg = 11;
int Ypos = 10;
int Yneg = 9;
int cas = 1;
int x1, y1, x2, y2, Xmove, Ymove;
const int stepsPerRevolution = 211;
int board_move[8][8][2] =
    {
    //Capital Letters are WHITE
      { {-2940,2940},{-2100,2940}, {-1260,2940}, {-420,2940}, {420,2940}, {1260,2940}, {2100,2940}, {2940,2940}},
      { {-2940,2100},{-2100,2100}, {-1260,2100}, {-420,2100}, {420,2100}, {1260,2100}, {2100,2100}, {2940,2100}},
      { {-2940,1260},{-2100,1260}, {-1260,1260}, {-420,1260}, {420,1260}, {1260,1260}, {2100,1260}, {2940,1260}},
      { {-2940,420}, {-2100,420}, {-1260,420}, {-420,420}, {420,420}, {1260,420}, {2100,420}, {2940,420}},
      { {-2940,-420}, {-2100,-420}, {-1260,-420}, {-420,-420}, {420,-420}, {1260,-420}, {2100,-420}, {2940,-420}},
      { {-2940,-1260}, {-2100,-1260}, {-1260,-1260}, {-420,-1260}, {420,-1260}, {1260,-1260}, {2100,-1260}, {2940,-1260}},
      { {-2940,-2100}, {-2100,-2100}, {-1260,-2100}, {-420,-2100}, {420,-2100}, {1260,-2100}, {2100,-2100}, {2940,-2100}},
      { {-2940,-2940}, {-2100,-2940}, {-1260,-2940}, {-420,-2940}, {420,-2940}, {1260,-2940}, {2100,-2940}, {2940,-2940}},
    };
const char initial_board[8][8] =
    {
    //Capital Letters are WHITE
      { 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
      { 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
      { 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
      { 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
      { 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
      { 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
      { 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
      { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
    };
Stepper myStepperX(stepsPerRevolution, 2,3);
Stepper myStepperY(stepsPerRevolution, 4,5);

void setup() {
  Serial.begin(9600);
  pinMode(Magbut, INPUT_PULLUP);
  pinMode(cas, INPUT_PULLUP);
  pinMode(Xpos, INPUT_PULLUP);
  pinMode(Xneg, INPUT_PULLUP);
  pinMode(Ypos, INPUT_PULLUP);
  pinMode(Yneg, INPUT_PULLUP);
  myStepperX.setSpeed(600);
  myStepperY.setSpeed(600);
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  // put your setup code here, to run once:

}

void loop() {
  int switchCase = digitalRead(Magbut);
  Case = 0;
  if(switchCase == HIGH){
      Case = Case+1;
      Serial.print(Case);
      if(Case > 6){Case=0;     
      }

  switch(Case){
    case 1:
      Serial.print("Choose Origin");
        while(1){
          buttonpress();
          x1 = XState;
          y1 = YState;
          OriginX = board_move[XState][YState][0];
          OriginY = board_move[XState][YState][1];
          int swit = digitalRead(Magbut);
          if(swit == HIGH){
            Serial.print(OriginX);
            Serial.print(OriginY);
            delay(1000);
           break;
          }
      }
    case 2:
      Serial.print("Choose Destination");
        while(1){
          buttonpress();
          x2 = XState;
          y2 = YState;
          DestinationX = board_move[XState][YState][0];
          DestinationY = board_move[XState][YState][1];
          int swit = digitalRead(Magbut);
          if(swit == HIGH){
            Serial.println(OriginX);
            Serial.println(OriginY);
            Serial.println(DestinationX);
            Serial.println(DestinationY);
            delay(1000);
           break;
          }
        }
    case 3:
      Serial.print("Initiate");
      while(1){
          moveX(x1*840-420);
          moveY(y1*840-420);

          delay(5000);
        
      }
      break;
    case 4:
      Serial.print("Initiate");
      while(1){
        while(switchCase == HIGH){
          moveX(x1*840-420);
          moveY(y1*840-420);

          delay(5000);
        }
      }
      break;
    case 5:
      
      break;
    case 6:
      
      break;
  }
  }

}

int buttonpress(){
  
  //int MagState = digitalRead(Magbut);
  int XposState = digitalRead(Xpos);
  int XnegState = digitalRead(Xneg);
  int YposState = digitalRead(Ypos);
  int YnegState = digitalRead(Yneg);
  if(XposState == HIGH){
      XState = XState+1;
      if(XState > 7){XState=0;     
      }
    }
    if(XnegState == HIGH){
      XState = XState-1;
      if(XState < 0){XState=7;         
      }
    }
    if(YposState == HIGH){
      YState = YState+1;
      if(YState > 7){YState=0;
      }       
    }
    if(YnegState == HIGH){
      YState = YState-1;
      if(YState < 0){YState=7;     
      }
    }
    lc.clearDisplay(0);
    lc.setLed(0,XState,YState,true);
      delay(120);

    if(XState != OldXState || YState != OldYState){
      lc.setLed(0,XState,YState,false);
      OldXState = XState;
      OldYState = YState;
    }
}
/*
int calc(int x[], int y[])
    {
    int a = x[0]-y[0];
    int b = x[1]-y[1];
    diff[0] = a;
    diff[1] = b;
return diff;
};
*/
void moveX(int x){
  myStepperX.step(x);
};

void moveY(int y){
  myStepperY.step(y);
};

int movePiece(){
  int MagState = digitalRead(Magbut);
    if(MagState == HIGH){
     // Xmove = board_move[XState][YState][0];
     // Ymove = board_move[XState][YState][1];
     moveX(XState*840-420);
     moveY(YState*840-420);

     delay(2000);
      moveY(-YState*840);
      moveX(XState*840);
      lc.setLed(0,XState,YState,true);
      
    }
}
/*
  int board_move[8][8][2] =
    {

    //Capital Letters are WHITE
    { {4,4}, {3,4}, {2,4}, {1,4}, {-1,4}, {-2,4}, {-3,4}, {-4,4} },
    { {4,3}, {3,3}, {2,3}, {1,3}, {-1,3}, {-2,3}, {-3,3}, {-4,3} },
    { {4,2}, {3,2}, {2,2}, {1,2}, {-1,2}, {-2,2}, {-3,2}, {-4,2} },
    { {4,1}, {3,1}, {2,1}, {1,1}, {-1,1}, {-2,1}, {-3,1}, {-4,1} },
    { {4,-1}, {3,-1}, {2,-1}, {1,-1}, {-1,-1}, {-2,-1}, {-3,-1}, {-4,-1} },
    { {4,-2}, {3,-2}, {2,-2}, {1,-2}, {-1,-2}, {-2,-2}, {-3,-2}, {-4,-2} },
    { {4,-3}, {3,-3}, {2,-3}, {1,-3}, {-1,-3}, {-2,-3}, {-3,-3}, {-4,-3} },
    { {4,-4}, {3,-4}, {2,-4}, {1,-4}, {-1,-4}, {-2,-4}, {-3,-4}, {-4,-4} },
  };


  int board_move[8][8][2] =
    {
    //Capital Letters are WHITE
      { {-2940,2940},{-2100,2940}, {-1260,2940}, {-420,2940}, {420,2940}, {1260,2940}, {2100,2940}, {2940,2940}},
      { {-2940,2100},{-2100,2100}, {-1260,2100}, {-420,2100}, {420,2100}, {1260,2100}, {2100,2100}, {2940,2100}},
      { {-2940,1260},{-2100,1260}, {-1260,1260}, {-420,1260}, {420,1260}, {1260,1260}, {2100,1260}, {2940,1260}},
      { {-2940,420}, {-2100,420}, {-1260,420}, {-420,420}, {420,420}, {1260,420}, {2100,420}, {2940,420}},
      { {-2940,-420}, {-2100,-420}, {-1260,-420}, {-420,-420}, {420,-420}, {1260,-420}, {2100,-420}, {2940,-420}},
      { {-2940,-1260}, {-2100,-1260}, {-1260,-1260}, {-420,-1260}, {420,-1260}, {1260,-1260}, {2100,-1260}, {2940,-1260}},
      { {-2940,-2100}, {-2100,-2100}, {-1260,-2100}, {-420,-2100}, {420,-2100}, {1260,-2100}, {2100,-2100}, {2940,-2100}},
      { {-2940,-2940}, {-2100,-2940}, {-1260,-2940}, {-420,-2940}, {420,-2940}, {1260,-2940}, {2100,-2940}, {2940,-2940}},
    };
    */
