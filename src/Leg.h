#ifndef LEG_H
#define LEG_H

#include "Vector.h"

class Leg
{
    public:
        Vector home;
        Vector origin;
        Vector target;

        // 0 = first joint, hip, closest to the body
        // 1 = second joint, knee, middle of the leg
        // 2 = third joint, wrist, end of the leg
        int pins[3];

        Leg(int pin0, int pin1, int pin2, float _x, float _y): origin(_x, _y, 0) {
            pins[0] = pin0;
            pins[1] = pin1;
            pins[2] = pin2;
        }

        void init();
        void setAngle(int joint_index, int angle);
        void setPin(int joint_index, int pin);
        void setPins(int joint_0, int joint_1, int joint_2);
};

#endif