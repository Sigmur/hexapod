#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "pca9685.h"

#include <chrono>
#include <math.h>
#include "Eigen/Dense"
#include "quik/geometry.hpp"
#include "quik/Robot.hpp"
#include "quik/IKSolver.hpp"

#include "defines.h"
#include "Hexapod.h"

using namespace std;
using namespace Eigen;

int pca_board_1 = -1;
int pca_board_2 = -1;

// Limb limbs[6];
/*
// Define the IK options
const quik::IKSolver<6> IKS(
    R, // The robot object (pointer)
    200, // max number of iterations
    quik::ALGORITHM_QUIK, // algorithm (ALGORITHM_QUIK, ALGORITHM_NR or ALGORITHM_BFGS)
    1e-12, // Exit tolerance
    1e-14, // Minimum step tolerance
    0.05, // iteration-to-iteration improvement tolerance (0.05 = 5% relative improvement)
    10, // max consequitive gradient fails
    80, // Max gradient fails
    1e-10, // lambda2 (lambda^2, the damping parameter for DQuIK and DNR)
    0.34, // Max linear error step
    1 // Max angular error step
);
*/

Hexapod hexapod;

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
        cout << "[ERROR] - Error while setting up PCA9685 board 1" << endl;
        return 1;
    }
    if (pca_board_2 < 0)
    {
        cout << "[ERROR] - Error while setting up PCA9685 board 2" << endl;
        return 1;
    }

    // 1.3) Reset all output
    cout << "BOARD1 : " << pca_board_1 << endl;
    cout << "BOARD2 : " << pca_board_2 << endl;
    pca9685PWMReset(pca_board_1);
    pca9685PWMReset(pca_board_2);

    // 2) Init Hexapod geometry & kinematics solvers
    if (!hexapod.init())
    {
        cout << "[ERROR] - Error while setting up the Hexapod" << endl;
        return 1;
    }
    
    /* Default pause
    leg 0 : x156    y200    z115
    leg 1 : x245    y0      z115
    leg 2 : x156    y-200   z115
    leg 0 : x-156   y200    z115
    leg 1 : x-245   y0      z115
    leg 2 : x-156   y-200   z115
    */

    /*
    double posx = 144 - 10;
    double posy = 188 - 10;

    Limb* leg0 = hexapod.getLimb(0);
    if (leg0->setEndTarget(posx, posy, -100))
    {
        cout << "A1" << endl;
        leg0->printAngles();
    }

    if (leg0->setEndTarget(-posx, posy, -100))
    {
        cout << "A2" << endl;
        leg0->printAngles();
    }

    if (leg0->setEndTarget(posx, -posy, -100))
    {
        cout << "A3" << endl;
        leg0->printAngles();
    }

    if (leg0->setEndTarget(-posx, -posy, -100))
    {
        cout << "A4" << endl;
        leg0->printAngles();
    }


    cout << "B1" << endl;
    int on;
    int off;
    cout << "B2 " << on << " - " << off << endl;
*/
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
