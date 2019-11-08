#ifndef _CTL_H
#define _CTL_H
#pragma once

char board[8][10] = 
    {
    //Capital Letters are WHITE
      {'0', 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R', '0'},
      {'0', 'A', 'C', 'D', 'E', 'F', 'G', 'H', 'P', '0'},
      {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
      {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
      {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
      {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
      {'0', 'a', 'c', 'd', 'e', 'f', 'g', 'h', 'p', '0'},
      {'0', 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r', '0'}
    };

int CTL(int xOrig,int yOrig,int xDest,int yDest,int turnn,int gyard,int arr[])
{
int turn = turnn; //0 is white turn
int casee = 0; //////////////////////////////////////////////////////////////////////////////////////////////////placeholder for switch control variable
int graveyard = gyard;


  int coordXorig = xOrig; /////////////////////////////////////////////////////////////////////////////////////////numbers will be received from input
  int coordYorig = yOrig + 1; ///
  int coordXdest = xDest; //
  int coordYdest = yDest + 1; //

  int inOrig = board[coordXorig][coordYorig]; //origin piece
  int inDest = board[coordXdest][coordYdest]; //dest piece
  Serial.print("Origin Piece: ");
  Serial.print(char(inOrig));
  Serial.print("   ");
  Serial.print("Dest Piece: ");
  Serial.print(char(inDest));
  Serial.print("   ");
  

if(turn == 0) //white turn
{
  if(inOrig >= 65 && inOrig <= 90 && inOrig != 48) //good orig - if piece is white (capital letter) and not vacant
  {
     board[coordXorig][coordYorig] = char(48); //set origin to vacant
     
     if(inDest == 48) //good dest - destination is vacant
     {
      board[coordXdest][coordYdest] = char(inOrig); //change dest to white piece
      Serial.print("Dest New Piece: ");
      Serial.print(char(board[coordXdest][coordYdest]));
      Serial.print("   ");
      turn = 1; /////set turn to black
      casee = 4; //push switch to next phase for movement
     }
     
     else if(inDest >=97 && inDest <= 122) //good dest - is black piece
     {
      graveyard++;
      if(graveyard > 0 && graveyard <= 8) //graveyard is in col #0
      {
       board[0][graveyard - 1] = char(inDest); //set captured piece to graveyard spot col #0
       turn = 1; /////set turn to black
       casee = 4; //push switch to next phase for movement
       Serial.print("Graveyard Piece: ");
       Serial.print(char(board[0][graveyard-1]));
       Serial.print("   ");
      }
      else if(graveyard > 8 && graveyard <= 16) //graveyard is in col #9
      {
        board[0][graveyard - 9] = char(inDest); //set captured piece to graveyard spot col #9
        turn = 1; /////set turn to black
       casee = 4; //push switch to next phase for movement
      }
      board[coordXdest][coordYdest] = char(inOrig); //change dest to white piece
      turn = 1; /////set turn to black
      casee = 4; //push switch to next phase for movement
     }
         
     else if(inDest >=65 && inDest <= 90) //bad dest - destination is white piece
     {
     casee = 1; ////restart switch to phase 1 for new input choices
     }
  }
  else if(inOrig == 48 || (inOrig >= 97 && inOrig <= 122)) //bad orig - origin is vacant or black
  {
    casee = 1; ////restart switch to phase 1 for new input choices
  }
  
}
else if(turn == 1) //black turn
{
  if(inOrig >= 97 && inOrig <= 122 && inOrig != 48) //good orig - if piece is black (lc letter) and not vacant
  {
     board[coordXorig][coordYorig] = char(48); //set origin to vacant
     
     if(inDest == 48) //good dest - destination is vacant
     {
      board[coordXdest][coordYdest] = char(inOrig); //change dest to black piece
      turn = 0;////set turn to white
      casee = 4; //push switch to next phase for movement
     }

     
     else if(inDest >=65 && inDest <= 90) //good dest, is white piece
    {
      graveyard++;
      if(graveyard > 0 && graveyard <= 8) //graveyard is in col #0
      {
        board[0][graveyard - 1] = char(inDest); //set captured piece to graveyard spot col #0
        turn = 0; /////set turn to white
      casee = 4; //push switch to next phase for movement
      }
      if(graveyard > 8 && graveyard <= 16) //graveyard is in col #9
      {
        board[0][graveyard - 9] = char(inDest); //set captured piece to graveyard spot col #9
        turn = 0; /////set turn to white
      casee = 4; //push switch to next phase for movement
      }
      board[coordXdest][coordYdest] = char(inOrig); //change dest to white piece
      turn = 0; /////set turn to white
      casee = 4; //push switch to next phase for movement
     }

     
     else if(inDest >=97 && inDest <= 122) //bad dest - destination is black piece
     {
      casee = 1; ////restart switch to phase 1 for new input choices
     }
  }
  else if(inOrig == 48 || inOrig >= 65 || inOrig <= 90) // bad orig - white piece or vacant
  {
    casee = 1; //restart switch to phase 1 for new input choices
  }
  
}
arr[0] = casee;
arr[1] = graveyard;
}

#endif // _CTL_H
