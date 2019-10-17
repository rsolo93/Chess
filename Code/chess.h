#ifndef _CHESS_H
#define _CHESS_H
#pragma once
#include <arduino.h>
#include <stddef.h>
#define EMPTY_SQUARE 0
class Chess
{
  public:
    static int getPieceColor(char chPiece);
    static bool isWhitePiece(char chPiece);
    static bool isBlackPiece(char chPiece);
    static String describePiece(char chPiece);
    enum PieceColor
    {
      WHITE_PIECE = 0,
      BLACK_PIECE = 1
    };
    enum Player
    {
      WHITE_PLAYER = 0,
      BLACK_PLATER = 1
    };
    enum Side
    {
      QUEEN_SIDE = 2,
      KING_SIDE = 3
    };
    enum Direction
    {
      HORIZONTAL = 0,
      VERTICAL,
      DIAGONAL,
      L_SHAPE,      
    };
    struct Position
    {
      int iRow;
      int iColumn;
    };
    struct IntendedMove
    {
      char chPiece;
      Position from;
      Position to;
    };
    struct Attacker
    {
      Position pos;
      Direction dir;
    };
    struct UnderAttack
    {
      bool bUnderAttack;
      int iNumAttackers;
      Attacker attacker[9];
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
};
class Game : Chess
{
public:

  Game();
  ~Game();

  void movePiece(Position present, Position future);
  char getPieceAtPosition(int iRow, int iColumn);
  char getPieceAtPosition(Position pos);
  char getPiece_considerMove(int iRow, int iColumn, IntendedMove* intended_move = NULL);
  UnderAttack isUnderAttack(int iRow, int iColumn, int iColor, IntendedMove* pintended_move = NULL);
  bool isReachable(int iRow, int iColumn, int iColor);
  bool isSquareOccupied(int iRow, int iColumn);
  bool isPathFree(int iRow, int iColumn);
  bool canBeBlocked(Position startingPos, Position finishingPos, int iDirection);
  bool isCheckmate();
  bool isKingCheck(int iColor, IntendedMove* intended_move = NULL);
  bool playerKingCheck(IntendedMove* intended_move = NULL);
  bool wouldKingBeCheck(char chPiece, Position present, Position future);
  Position findKing(int iColor);
  void changeTurns(void);
  bool isFinished(void);
  int getCurrentTurn(void);
  int getOpponentColor(void);
  int parseMove(String move, Position* pFrom, Position* pTo);
  void logMove(String &to_record);
  String getLastMove(void);

private:

char board[8][8];
int m_CurrentTurn;
bool m_bGameFinished;

};




#endif // _CHESS_H
