#ifndef UTILS_H
#define UTILS_H

class Utils
{
    public: 
        static int mapInt(int x, int in_min, int in_max, int out_min, int out_max)
        { // Taken from arduino source code
            return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
        }

        static float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
        { // Taken from arduino source code
            return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
        }

};

#endif