#include "LedControl.h"
#include "MCP23017.h"
#include <Wire.h>
#include <Stepper.h>
#include <SharpIR.h>
LedControl lc = LedControl(6,7,8,1);
MCP23017 mcp;
int XState, YState, OldXState, OldYState, Case, OriginX, OriginY, DestinationX, DestinationY, xmove, ymove, casee;
int x1, y1, x2, y2, Xmove, Ymove;
const int stepsPerRevolution = 211;
int board_move[8][8][2] =
{
      { {1,1},  {2,1},  {3,1},  {4,1},  {5,1},  {6,1},  {7,1},  {8,1}  },
      { {1,2},  {2,2},  {3,2},  {4,2},  {5,2},  {6,2},  {7,2},  {8,2}  },
      { {1,3},  {2,3},  {3,3},  {4,3},  {5,3},  {6,3},  {7,3},  {8,3}  },
      { {1,4},  {2,4},  {3,4},  {4,4},  {5,3},  {6,4},  {7,4},  {8,4}  },
      { {1,5},  {2,5},  {3,5},  {4,5},  {5,5},  {6,5},  {7,5},  {8,5}  },
      { {1,6},  {2,6},  {3,6},  {4,6},  {5,6},  {6,6},  {7,6},  {8,6}  },
      { {1,7},  {2,7},  {3,7},  {4,7},  {5,7},  {6,7},  {7,7},  {8,7}  },
      { {1,8},  {2,8},  {3,8},  {4,8},  {5,8},  {6,8},  {7,8},  {8,8}  },
    };
Stepper myStepperX(stepsPerRevolution, 2,3);
Stepper myStepperY(stepsPerRevolution, 4,5);

void setup() {
  Serial.begin(9600);
  mcp.begin(7);
  
  mcp.pinMode(0, INPUT_PULLUP);    //Magbut
  mcp.pinMode(1, INPUT_PULLUP);    //Xpos
  mcp.pinMode(2, INPUT_PULLUP);    //Yneg
  mcp.pinMode(3, INPUT_PULLUP);    //Ypos
  mcp.pinMode(4, INPUT_PULLUP);    //Yneg
  mcp.pinMode(5, INPUT); //Limitswitch 1
  mcp.pinMode(6, INPUT); //Limitswitch 2
  myStepperX.setSpeed(600);
  myStepperY.setSpeed(600);
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  homing();
  // put your setup code here, to run once:

}

void loop() {
  int switchCase = mcp.digitalRead(0);
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
          int swit = mcp.digitalRead(0);
          if(swit == HIGH){
            OriginX = board_move[XState][YState][0];
            OriginY = board_move[XState][YState][1];
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
          int swit = mcp.digitalRead(0);
          if(swit == HIGH){
            DestinationX = board_move[XState][YState][0];
            DestinationY = board_move[XState][YState][1];
            delay(1000);
           break;
          }
        }
    case 3:
      CTL(OriginX, OriginY, DestinationX, DestinationY);
      Case = casee;
      break;
     
    case 4:
      Serial.println("Initiate Moving Piece");
      Serial.print("xmove is ");
      Serial.print(xmove);
      Serial.print(" ");
      Serial.print("ymove is ");
      Serial.println(ymove);
      moveX(OriginX*840);
      moveY(OriginY*840);
      moveX(-420);
      moveY(-420);
      delay(5000);
      moveX(420);
      moveY(420);
      Origin2Dest();
      moveX(xmove);
      moveY(ymove);
      delay(5000);
      homing();
       
      Serial.println("Done");
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
  int XposState = mcp.digitalRead(1);
  int XnegState = mcp.digitalRead(2);
  int YposState = mcp.digitalRead(3);
  int YnegState = mcp.digitalRead(4);
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

void homing(){
  int Limit1 = mcp.digitalRead(5);
  int Limit2 = mcp.digitalRead(6);
  if(Limit1 != HIGH)
    for(int s=0; s<stepsPerRevolution; s++)
      myStepperX.step(1);    // I have not checked to see if the X or Y motors are to move in the + or - direction
  if(Limit2 != HIGH)
    for(int s=0; s<stepsPerRevolution; s++)
      myStepperY.step(1);
};

void moveX(int x){
  myStepperX.step(x);
};

void moveY(int y){
  myStepperY.step(y);
};

int Origin2Dest(){
    if(OriginX > DestinationX)
       xmove = abs((DestinationX-OriginX));
       else
       xmove = -abs(DestinationX-OriginX);

       if(OriginY > DestinationY)
       ymove = abs(DestinationY-OriginY);
       else
       ymove = -abs(DestinationY-OriginY);
}

int CTL(int xOrig,int yOrig,int xDest,int yDest){
  int turn = 0; //0 is white turn
  char board[8][10] =
      {
      //Capital Letters are WHITE
        {'0', 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R', '0'},
        {'0', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', '0'},
        {'0', 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r', '0'}
      };
  
    int coordXorig = xOrig; 
    int coordYorig = yOrig; 
    int coordXdest = xDest; 
    int coordYdest = yDest; 
  
    int inOrig = board[coordXorig][coordYorig];
    int inDest = board[coordXdest][coordYdest];
  
  if(turn == 0) //white turn
  {
    if(inOrig >= 65 && inOrig <= 90 && inOrig != 48) //good orig - if piece is white (capital letter) and not vacant
    {
       board[coordXorig][coordYorig] = char(48); //set origin to vacant
       
       if(inDest == 48 || (inDest >=97 && inDest <= 122)) //good dest - destination is vacant or black piece
       {
        board[coordXdest][coordYdest] = char(inOrig); //change dest to white piece
        turn = 1; /////set turn to black
        casee = 4; //push switch to next phase for movement
       }
           
       else if(inDest >=65 && inDest <= 90) //bad dest - destination is white piece
       {
       casee = 1; ////restart switch to phase 1 for new input choices
       }
    }
    else if(inOrig == 48 || inOrig >= 97 || inOrig <= 122) //bad orig - origin is vacant or black
    {
      casee = 1; ////restart switch to phase 1 for new input choices
    }
    
  }
  if(turn == 1) //black turn
  {
    if(inOrig >= 97 && inOrig <= 122 && inOrig != 48) //good orig - if piece is black (lc letter) and not vacant
    {
       board[coordXorig][coordYorig] = char(48); //set origin to vacant
       
       if(inDest == 48 || (inDest >=65 && inDest <= 90)) //good dest - destination is vacant or white piece
       {
        board[coordXdest][coordYdest] = char(inOrig); //change dest to black piece
        turn = 0;////set turn to white
        casee = 4; //push switch to next phase for movement
       }
       
       else if(inDest >=97 && inDest <= 122) //bad dest - destination is black piece
       {
        casee = 1; ////restart switch to phase 1 for new input choices
       }
    }
    else if(inOrig == 48 || inOrig >= 65 || inOrig <= 90)
    {
      // bad orig - white piece or vacant
      casee = 1; //restart switch to phase 1 for new input choices
    }
    
}
return casee;
}

void graveyard(){
  moveX(DestinationX*840);
  moveY(DestinationY*840);
  delay(1000);
}
