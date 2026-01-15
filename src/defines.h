#ifndef DEFINES_H
#define DEFINES_H

/* Leg servo pinouts 
1. = PCA board 1
2. = PCA board 2
*/
#define LEG_0 0 //right front  | Pins 1.0 | 1.8  | 2.0
#define LEG_1 1 //right middle | Pins 1.1 | 1.9  | 2.1
#define LEG_2 2 //right back   | Pins 1.2 | 1.10 | 2.2
#define LEG_3 3 //left front   | Pins 1.3 | 1.11 | 2.3
#define LEG_4 4 //left middle  | Pins 1.4 | 1.12 | 2.4
#define LEG_5 5 //left back    | Pins 1.5 | 1.13 | 2.5

#define BOARD1_PIN_BASE 100
#define BOARD2_PIN_BASE 120

#define PCA9685_FREQUENCY 50  // 50Hz
#define MIN_MS 0.5            // 0° = 102
#define MAX_MS 2.5            // 180° = 512
#define MIN_DUTY 102          //0°
#define MAX_DUTY 512          //180°

#endif