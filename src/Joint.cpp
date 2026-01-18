#include "Joint.h"
#include <math.h>
#include <wiringPi.h>
#include "pca9685.h"
#include "defines.h"
#include "utils.h"

void Joint::init()
{
    // Move to home angle
    moveJoint();
}

void Joint::update()
{
}

// -----

void Joint::setAngle(float _angle, bool move)
{
    boxAngle(_angle);
    angle = _angle;

    if (move) // Update servo position if called for
        moveJoint();
}

void Joint::setHome(float angle)
{
    boxAngle(angle);
    home = angle;
}

void Joint::setTarget(float angle)
{
    boxAngle(angle);
    target = angle;
}

void Joint::setMinAngle(float angle)
{
    boxAngle(angle);
    min_angle = angle;
}

void Joint::setMaxAngle(float angle)
{
    boxAngle(angle);
    max_angle = angle;
}

void Joint::setPin(int _pin)
{
    pin = _pin;
}

// -----

void Joint::moveJoint()
{
    // 1) Transform angle into PWM duty cycle
    duty_cycle = (int)Utils::mapFloat(angle, 0, 180, MIN_DUTY, MAX_DUTY);

    // 2) Send to PCA9685
    pwmWrite(pin, duty_cycle);
}

bool Joint::isValidAngle(float _angle)
{
    return (_angle >= min_angle && _angle <= max_angle);
}

void Joint::boxAngle(float& _angle)
{ // Check if given angle is within min & max, update it to fit if not
    if (_angle < min_angle)
        _angle = min_angle;
    if (_angle > max_angle)
        _angle = max_angle;
}