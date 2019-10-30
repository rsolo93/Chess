
#include "chess.h"
Game* current_game = NULL;

void makeMove(Chess::Position present, Chess::Position future)
{
  char chPiece = current_game->getPieceAtPosition(present.iRow, present.iColumn);

  //captured piece?
  if ( current_game->isSquareOccupied(future.iRow, future.iColumn) )
   {
      char chAuxPiece = current_game->getPieceAtPosition(future.iRow, future.iColumn);

      if ( Chess::getPieceColor(chPiece) != Chess::getPieceColor(chAuxPiece))
      {
         ///////////////////////////////put code for captured piece here
      }
      else
      {
         //////////////////////////////////code for resetting turn
      }
   }
}
void newGame(void)
{
   if (NULL != current_game)
   {
      delete current_game;
   }

   current_game = new Game();
}

void movePiece(void)
{
   String to_record;

   // Get user input for the piece they want to move
   String move_from;
   ///////////////////////////code for retreiving input of desired piece location

   Chess::Position present;
   present.iColumn = move_from[0];
   present.iRow    = move_from[1];

   // Convert column from ['A'-'H'] to [0x00-0x07]
   present.iColumn = present.iColumn - 'A';

   // Convert row from ['1'-'8'] to [0x00-0x07]
   present.iRow  = present.iRow  - '1';

   char chPiece = current_game->getPieceAtPosition(present.iRow, present.iColumn);
   
   if ( 'O' == chPiece )
   {
      ///////////////////////////////code for selecting empty space
   }

   if ( Chess::WHITE_PIECE == current_game->getCurrentTurn() )
   {
      if ( false == Chess::isWhitePiece(chPiece) )
      {
         ///////////////////////////////code for white turn picked black piece
         return;
      }
   }
   else
   {
      if ( false == Chess::isBlackPiece(chPiece) )
      {
         ////////////////////////////////////////code for black turn picked white piece
         return;
      }
   }

   // ---------------------------------------------------
   // Get user input for the square to move to
   // ---------------------------------------------------
  
   String move_to;
   /////////////////////////////////////////code for receiving user input for destination
   return;
}
   

void setup() {
  // put your main code here, to run repeatedly:

}
void loop() {
  // put your main code here, to run repeatedly:

}
