#include "LedControl.h"
#include <stddef.h>
#include <Stepper.h>

int XState;
int YState;
int OldYState;
int OldXState;
int Magbut = 13;
int Xpos = 12;
int Xneg = 11;
int Ypos = 10;
int Yneg = 9;
int XmoveO;
int YmoveO;
int XmoveD;
int YmoveD;
int counter;
int a;
int b;
 const int halfstep = 420;
 const int fullstep = halfstep*2;
 const int stepsPerRevolution = 211;

 LedControl lc = LedControl(6,7,8,1);
Stepper myStepperX(stepsPerRevolution, 2,3);
Stepper myStepperY(stepsPerRevolution, 4,5);
     const char initial_board[8][11] =
    {
    //Capital Letters are White, Lower Case Black
      { 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R', 'O', 'O', 'O'},
      { 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'O', 'O', 'O'},
      { 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
      { 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
      { 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
      { 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
      { 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'O', 'O', 'O'},
      { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r', 'O', 'O', 'O'},
    };
/*
    void diff(int destination[], int origin[])
    {
        int x1 = origin[0];
        int y1 = origin[0];
        int x2 = destination[1];
        int y2 = destination[1];

        int diff[0] = x2-x1;
        int diff[1] = y2-y1;
        return diff;
    };*/

    
//const int stepsPerRevolution = 420;


int buttonpress(){
  
  int MagState = digitalRead(Magbut);
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

    void moveX(int x)
    {
        myStepperX.step(x);
    };

    void moveY(int y)
    {
        myStepperY.step(y);
    };


int movePiece(){
int MagState = digitalRead(Magbut);
counter = 0;
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
    
    if(MagState == HIGH && counter == 0){
      XmoveO = XState;
      YmoveO= YState;
       delay(1000);
      counter = 1;   
    }
      if(MagState == HIGH && counter == 1){
      XmoveD = XState;
      YmoveD= YState;
      delay(1000);
      counter = 2;  
      } 
 int a = (XmoveD-XmoveO)*840;
 int b = (YmoveD-YmoveO)*840;

    if(MagState == HIGH && counter == 2){
     moveX(XmoveD*-840);
     moveY(YmoveD*840);
     counter = 0;
     XmoveO=0;
     YmoveO=0;
     XmoveD=0;
     YmoveD =0;
    }

    
}


    
/*
int main()
{
    switch(phase)
    {

        // in setup board initial setup initializes
        
        case 0:
        //Player Selection
        break;

        case 1:
        //Piece Selection - Origin - Destination
        break;
        
        case 2:
        // If Destination != 0 - Graveyard Movement
        //If Destination = 0; phase = 3;
        break;

        case 3:
        //Piece Movement
        break;

        case 4:
Multiple libraries were found for "Stepper.h"
 Used: /home/riley/Downloads/arduino-1.8.10-linux64/arduino-1.8.10/libraries/Stepper
exit status 1
        // Home? 
        break;

    }
}

} */
