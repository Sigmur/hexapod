#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "pca9685.h"
#include "defines.h"

#include "Leg.h"

using namespace std;

int pca_board_1 = -1;
int pca_board_2 = -1;

Leg legs[6];

int setup()
{
    // 1) ---- PCA9685 ----
    // 1.1) Init wiringPi
    wiringPiSetup();

    // 1.2) Open link to boards
    pca_board_1 = pca9685Setup(BOARD1_PIN_BASE, 0x40, PCA9685_FREQUENCY);
    pca_board_2 = pca9685Setup(BOARD2_PIN_BASE, 0x41, PCA9685_FREQUENCY);
    if (pca_board_1 < 0)
    {
        cout << "Error while setting up PCA9685 board 1" << endl;
        return 1;
    }
    if (pca_board_2 < 0)
    {
        cout << "Error while setting up PCA9685 board 2" << endl;
        return 1;
    }

    // 1.3) Reset all output
    pca9685PWMReset(pca_board_1);
    pca9685PWMReset(pca_board_2);

    // 2) ---- Legs ----
    // 2.1) Setup pins
    legs[1] = Leg(BOARD1_PIN_BASE + 0, BOARD1_PIN_BASE + 8, BOARD2_PIN_BASE + 0);
    legs[2] = Leg(BOARD1_PIN_BASE + 1, BOARD1_PIN_BASE + 9, BOARD2_PIN_BASE + 1);
    legs[3] = Leg(BOARD1_PIN_BASE + 2, BOARD1_PIN_BASE + 10, BOARD2_PIN_BASE + 2);
    legs[4] = Leg(BOARD1_PIN_BASE + 3, BOARD1_PIN_BASE + 11, BOARD2_PIN_BASE + 3);
    legs[5] = Leg(BOARD1_PIN_BASE + 4, BOARD1_PIN_BASE + 12, BOARD2_PIN_BASE + 4);
    legs[6] = Leg(BOARD1_PIN_BASE + 5, BOARD1_PIN_BASE + 13, BOARD2_PIN_BASE + 5);
    
    // 2.2) Move to base angle
    for (uint8_t i = 0; i < 6; i++)
        legs[i].init();

   return 0;
}

int loop()
{
   return 1;
}

int main()
{
   cout << "1 - Init" << endl;

   cout << "2 - Setup" << endl;
   if (setup())
      return 1;
   cout << "2 - Done !" << endl;

   cout << "3 - Start loop" << endl;
   while(loop()) {}
   cout << "3 - Exited loop" << endl;

   return 0;
}
