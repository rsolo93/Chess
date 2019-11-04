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

int x;
int y;
bool origin = false;
bool destination = false;
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

    void moveX(int mx)
    {
        myStepperX.step(mx);
    };

    void moveY(int my)
    {
        myStepperY.step(my);
    };


int Origin(){
  origin == true;
  destination == false;
int MagState = digitalRead(Magbut);

    if(MagState == HIGH && origin == true) {
     x = board_move[XState][YState][0];
     y = board_move[XState][YState][1];
    /*
    Serial.print(result[0]);
    Serial.print(" | ");
    Serial.print(result[1]);*/
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
    /*
    Serial.print(result[0]);
    Serial.print(" | ");
    Serial.print(result[1]);*/
    return a, b;
    }
}

    /*
      if(MagState == HIGH && counter == 1){
       DestinationX = board_move[XState][YState][0];
       DestinationY = board_move[XState][YState][1];
      delay(1000);
      Serial.print("Counter is: ");
      Serial.println(counter);

      counter++;  
      }

    int Xmove = calc(DestinationX, OriginX);   
    int Ymove = calc(DestinationY, OriginY);
    if(MagState == HIGH && counter == 2){
     moveX(Xmove*840);
     delay(100);
     moveY(Ymove*840);
     delay(1000);
      Serial.print("Counter is: ");
      Serial.println(counter);


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
