#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
    public:
        float x;
        float y;
        float z;

    public:
        Vector(float _x = 0.0, float _y = 0.0, float _z = 0.0) : x(_x), y(_y), z(_z) {}
};

#endif