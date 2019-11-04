#ifndef _CTL_H
#define _CTL_H
#pragma once


int CTL(int xOrig,int yOrig,int xDest,int yDest)
{
int turn = 0; //0 is white turn
int casee = 0; //////////////////////////////////////////////////////////////////////////////////////////////////placeholder for switch control variable
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

  int coordXorig = 0; /////////////////////////////////////////////////////////////////////////////////////////numbers will be received from input
  int coordYorig = 0; //
  int coordXdest = 0; //
  int coordYdest = 0; //

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

#endif // _CTL_H
