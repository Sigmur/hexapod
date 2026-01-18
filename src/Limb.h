#ifndef LIMB_H
#define v_H

// Arbitrary max joint count for a limb, just to init the array
#define MAX_JOINT_COUNT 8

#include "Vector.h"
#include "Joint.h"

class Limb
{
    private:
        int joint_count;
        Joint* joints[MAX_JOINT_COUNT];

    public:
        Limb() {};
        void init();
        // -----
        Joint* addJoint(int pin = DEFAULT_JOINT_PIN, float length = 0.0f, float home_angle = 90.0f, float min_angle = 0.0f, float max_angle = 180.0f);
        Joint* addJoint(int pin = DEFAULT_JOINT_PIN);
        Joint* getJoint(int index);
        int getJointCount();
        bool hasJoints();
        bool hasJoint(int index);
};

#endif