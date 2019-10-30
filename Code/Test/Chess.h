
#include <stddef.h>
#include <Stepper.h>

    
 const int halfstep = 420;
 const int fullstep = halfstep*2;
 const int stepsPerRevolution = 211;
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

    void moveX(int x)
    {
        myStepperX.step(x);
    };

    void moveY(int y)
    {
        myStepperY.step(y);
    };
    
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
