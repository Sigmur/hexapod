#include "Leg.h"
#include <math.h>
#include <wiringPi.h>
#include "pca9685.h"
#include "defines.h"

void Leg::init()
{
    origin.z = atan2(origin.y, origin.x); // neutral angle

    // Move everything to base position
    setAngle(0, 90);
    setAngle(1, 90);
    setAngle(2, 90);
}

void Leg::setAngle(int joint_index, int angle)
{
    // 1) Check target joint
    if (joint_index < 0 || joint_index > 2)
        return ; // Wrong index

    // 2) Check angle
    if (angle < 0)
        angle = 0;
    if (angle > 180)
        angle = 180;

    // 3) Transform angle into PWM duty cycle
    angle = map(angle, 0, 180, MIN_DUTY, MAX_DUTY);

    // 4) Send to PCA9685
    pwmWrite(pins[joint_index], angle);
}

void Leg::setPin(int joint_index, int pin)
{
    if (joint_index < 0 || joint_index > 2)
        return ; // Wrong index

    pins[joint_index] = pin;
}

void Leg::setPins(int joint_0, int joint_1, int joint_2)
{
    setPin(0, joint_0);
    setPin(1, joint_1);
    setPin(2, joint_2);
}