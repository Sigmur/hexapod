#ifndef DEFINES_H
#define DEFINES_H

#define RAD_TO_DEG(x) ((x) * 180.0 / M_PI)
#define DEG_TO_RAD(x) ((x) * M_PI / 180.0)
#define POW2(x)       ((x)*(x))

#define DEBUG

// ----- SERVO -----
#define BOARD1_PIN_BASE 200
#define BOARD2_PIN_BASE 300

#define PCA9685_FREQUENCY 50  // 50Hz
#define MIN_MS 0.5            // 0° = 102
#define MAX_MS 2.5            // 180° = 512
#define MIN_DUTY 102          //0°
#define MAX_DUTY 512          //180°

// ----- LIMBS -----
#define LIMB_COUNT 6                // Hexapod have 6 legs, i checked
#define LIMB_DOF 3                  // 3 Degrees Of Freefom (DOF) : 3 joints
// DEFAULT ANGLES
#define LIMB_JOINT1_ANGLE 90.0f
#define LIMB_JOINT2_ANGLE 90.0f
#define LIMB_JOINT3_ANGLE 100.0f
// LENGHTS
#define LIMB_LENGTH_PART1 38.0      // Coxia
#define LIMB_LENGTH_PART2 86.25     // Femur
#define LIMB_LENGTH_PART3 160.5     // Tibia

#endif