#ifndef __VECTOR__
#define __VECTOR__

#include <iostream>
#include <algorithm>
#include <cmath>

class VECTOR
{

public:
    /*
    * Three coordinate of a vector
    */
    float x;
    float y;
    float z;

    //default constructor just for the purpose of avoiding core dump error
    VECTOR() : x(0), y(0), z(0) {};

    VECTOR(float x, float y, float z);

    VECTOR invert();
    float magnitude();
    VECTOR normalize();
    VECTOR multiply(float number);
    VECTOR multiply(const VECTOR& vector);
    VECTOR add(const VECTOR& vector);
    VECTOR substract(const VECTOR& vector);
    VECTOR divide(float number);
    VECTOR divide(VECTOR vector);
    VECTOR componentProduct(const VECTOR& vector);
    float scalarProduct(const VECTOR& vector);
    VECTOR vectorProduct(const VECTOR& vector);
    VECTOR direction();
    void clear();
};

#endif // __TIMER__
