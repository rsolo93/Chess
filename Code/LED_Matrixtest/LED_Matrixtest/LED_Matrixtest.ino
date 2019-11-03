#include "LedControl.h"
#include <Stepper.h>
#include <SharpIR.h>
LedControl lc = LedControl(6,7,8,1);
int XState;
int YState;
int Case;
int OldYState;
int OldXState;
int Magbut = 13;
int Xpos = 12;
int Xneg = 11;
int Ypos = 10;
int Yneg = 9;
int cas = 14;
int Xmove;
int Ymove;
const int stepsPerRevolution = 211;
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
  pinMode(Magbut, INPUT);
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
  int switchCase = digitalRead(cas);
  Case = 2;
  if(switchCase == HIGH){
      Case = Case+1;
      if(Case > 6){Case=0;     
      }
    }
  switch(Case){
    case 1:
      Serial.print("Choose Origin");
      while(switchCase != HIGH){
      buttonpress();
      int x1 = XState;
      int y1 = YState;
      }
      break;
    case 2:
      Serial.print("Choose Destination");
      while(switchCase != HIGH){
        buttonpress();
        int x2 = 57;
        int y2 = YState;
        Serial.println(x2);
      }
      break;
    case 3:
      Serial.print("Initiate");
      while(1){
        while(switchCase == HIGH){
          moveX(x1*840-420);
          moveY(y1*840-420);

          delay(5000);
        }
      }
      break;
    case 4:
      
      break;
    case 5:
      
      break;
    case 6:
      
      break;
  }

  Serial.println(Ymove);

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
      int OldXState = XState;
      int OldYState = YState;
    }
}

void moveX(int x){
  myStepperX.step(x);
};

void moveY(int y){
  myStepperY.step(y);
};

int movePiece(){
  int MagState = digitalRead(Magbut);
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
    int count = 1;
    if(MagState == HIGH && count == 1){
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
