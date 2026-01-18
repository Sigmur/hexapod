#include "Limb.h"
#include "Joint.h"
#include <math.h>

void Limb::init()
{
    if (!hasJoints())
        return; // Nothing to do

    // 1) TODO - Precalculate stuff
    // origin.z = atan2(origin.y, origin.x); // neutral angle

    // 2) Move joints to base positions
    for (int i = 0; i < joint_count; i++)
        joints[i]->init();
}

// ------

Joint* Limb::addJoint(int pin, float length, float home_angle, float min_angle, float max_angle)
{
    // 1) Check if we have enough space for more joints
    if (joint_count == MAX_JOINT_COUNT)
        return NULL; // -1 is invalid joint index, meaning none was added

    // 2) Init the joint
    Joint* joint = new Joint(pin, length, home_angle, min_angle, max_angle);
    if (!joint) // Could not init the joint properly
        return NULL;

    // 3) Add the joint to the limb
    joints[joint_count++] = joint;

    return joint;
}

int Limb::getJointCount()
{
    return joint_count;
}

bool Limb::hasJoints()
{
    return joint_count > 0;
}

bool Limb::hasJoint(int index)
{
    return (index >= 0 && index < joint_count);
}


