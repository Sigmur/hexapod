#ifndef JOINT_H
#define JOINT_H

//  arbitraty, taken from the PCA9685 example code, can be anything above 100
#define DEFAULT_JOINT_PIN 300

class Joint
{
    private:
        int duty_cycle;     // PWM duty cycle to sent to servo
        int pin;            // Pin used to call servo movement

    public:
        float length;       // Length in mm from previous joint, 0 if first
        // Angles are in ° from 0 to 360
        float angle;        // current angle
        float home;         // home angle, default position
        float target;       // target angle to go to
        // Min & max angles are for targeted positions, not full servo range of movement
        float min_angle;    // min angle, values under this will be ignored
        float max_angle;    // max angle, values over this will be ignored

        Joint(int _pin = DEFAULT_JOINT_PIN, float _length = 0.0f, float _home = 90.0f, float _min_angle = 0.0f, float _max_angle = 180.0f): 
            pin(_pin), 
            length(_length),
            home(_home),
            target(_home),
            min_angle(_min_angle),
            max_angle(_max_angle)
        {
            angle = _home;
        }

        bool init();
        void update();
        void updateServoPosition();
        // -----
        void setAngle(float _angle, bool move = true);
        void setHome(float angle);
        void setTarget(float angle);
        void setMinAngle(float angle);
        void setMaxAngle(float angle);
        void setPin(int _pin);
        // -----

    private:
        bool isValidAngle(float _angle);
        void boxAngle(float &_angle);
};

#endif