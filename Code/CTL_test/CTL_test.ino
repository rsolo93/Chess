#include "CTL.h"

void setup() {

  ///turn one
  Serial.begin(9600);
  int turn,graveyard,casee = 0;
  int arr[2] = {0,0};
  int xorig, yorig, xdest, ydest;
  xorig = 0;
  yorig = 0;
  xdest = 6;
  ydest = 5;
  CTL(xorig,yorig,xdest,ydest,turn,graveyard,arr);
  casee = arr[0];
  graveyard = arr[1];
  Serial.print("graveyard spot ");
  Serial.print(graveyard);
  Serial.print("   ");
  Serial.print("casee ");
  Serial.print(casee);
  Serial.print('\n');
 //turn two
  turn = 1; 
  xorig = 6;
  yorig = 6;
  xdest = 1;
  ydest = 6;
  CTL(xorig,yorig,xdest,ydest,turn,graveyard,arr);
  casee = arr[0];
  graveyard = arr[1];
  Serial.print("graveyard spot ");
  Serial.print(graveyard);
  Serial.print("   ");
  Serial.print("casee ");
  Serial.print(casee);
  Serial.print('\n');

 //turn 3 
  turn = 0; 
  xorig = 1;
  yorig = 3;
  xdest = 3;
  ydest = 3;
  CTL(xorig,yorig,xdest,ydest,turn,graveyard,arr);
  casee = arr[0];
  graveyard = arr[1];
  Serial.print("graveyard spot ");
  Serial.print(graveyard);
  Serial.print("   ");
  Serial.print("casee ");
  Serial.print(casee);
  Serial.print('\n');
}

void loop() {

}
