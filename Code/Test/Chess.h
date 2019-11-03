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
int OriginX;
int OriginY;
int DestinationX;
int DestinationY;
int counter;
int a;
int b;
int diff[2];
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

    int calc(int x[], int y[])
    {
        int a = x[0]-y[0];
        int b = x[1]-y[1];
        diff[0] = a;
        diff[1] = b;
        return diff;
    };

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
 /* int board_move[8][8][2] =
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
    };*/
     int board_move[8][8][2] =
    {
      
    //Capital Letters are WHITE
      { {4,4},  {3,4},  {2,4},  {1,4},  {-1,4},  {-2,4},  {-3,4},  {-4,4}  },
      { {4,3},  {3,3},  {2,3},  {1,3},  {-1,3},  {-2,3},  {-3,3},  {-4,3}  },
      { {4,2},  {3,2},  {2,2},  {1,2},  {-1,2},  {-2,2},  {-3,2},  {-4,2}  },
      { {4,1},  {3,1},  {2,1},  {1,1},  {-1,1},  {-2,1},  {-3,1},  {-4,1}  },
      { {4,-1}, {3,-1}, {2,-1}, {1,-1}, {-1,-1}, {-2,-1}, {-3,-1}, {-4,-1} },
      { {4,-2}, {3,-2}, {2,-2}, {1,-2}, {-1,-2}, {-2,-2}, {-3,-2}, {-4,-2} },
      { {4,-3}, {3,-3}, {2,-3}, {1,-3}, {-1,-3}, {-2,-3}, {-3,-3}, {-4,-3} },
      { {4,-4}, {3,-4}, {2,-4}, {1,-4}, {-1,-4}, {-2,-4}, {-3,-4}, {-4,-4} },
    };
    
    if(MagState == HIGH && counter == 0){
     OriginX = board_move[XState][YState][0];
     OriginY = board_move[XState][YState][1];
       delay(1000);
      counter+=1;   
    }
      if(MagState == HIGH && counter == 1){
       DestinationX = board_move[XState][YState][0];
       DestinationY = board_move[XState][YState][1];
      delay(1000);
      counter+=1;  
      }

    int Xmove = calc(DestinationX, OriginX);   
    int Ymove = calc(DestinationY, OriginY);
    if(MagState == HIGH && counter == 2){
     moveX(Xmove*840);
     moveY(Ymove*840);
     counter = 0;
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
