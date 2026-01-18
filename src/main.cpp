#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "pca9685.h"
#include "defines.h"

#include "Limb.h"

#define JOINT1_ANGLE 90.0f
#define JOINT2_ANGLE 125.0f
#define JOINT3_ANGLE 110.0f

#define LIMB_LENGTH_PART1 38.0
#define LIMB_LENGTH_PART2 86.25
#define LIMB_LENGTH_PART3 160.5

using namespace std;

int pca_board_1 = -1;
int pca_board_2 = -1;

Limb limbs[6];

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
    // 2.1) Setup joints
    for (int i = 0; i < 6; i++)
    {
        /* Limb pins : 
            - Board 1 : 0-5  = first joints
            - Board 1 : 8-13 = second joints
            - Board 2 : 0-6  = third joints
        */
        limbs[i].addJoint(BOARD1_PIN_BASE + 0 + i, LIMB_LENGTH_PART1, JOINT1_ANGLE, 5.0f, 85.0f);
        limbs[i].addJoint(BOARD1_PIN_BASE + 8 + i, LIMB_LENGTH_PART2, JOINT2_ANGLE, 5.0f, 85.0f);
        limbs[i].addJoint(BOARD2_PIN_BASE + 0 + i, LIMB_LENGTH_PART3, JOINT3_ANGLE, 5.0f, 85.0f);
        limbs[i].init();
    }

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
