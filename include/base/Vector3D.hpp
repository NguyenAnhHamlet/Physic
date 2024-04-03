#ifndef __VECTOR__
#define __VECTOR__

#include <iostream>
#include <algorithm>
#include <cmath>

class Vector3D
{
public:
    /*
    * Three coordinate of a vector
    */
    float x;
    float y;
    float z;

    //default constructor just for the purpose of avoiding core dump error
    Vector3D() : x(0), y(0), z(0) {};

    Vector3D(float x, float y, float z);

    //operator overloading with instance
    void operator=(const Vector3D& vector);
    Vector3D operator+(const Vector3D& vector);
    Vector3D operator-(const Vector3D& vector);
    Vector3D operator*(float number);
    Vector3D operator*(const Vector3D& vector);
    Vector3D operator/(Vector3D vector);
    Vector3D operator/(float number);

    Vector3D invert();
    float magnitude();
    Vector3D normalize();
    Vector3D componentProduct(const Vector3D& vector);
    float scalarProduct(const Vector3D& vector);
    float dotProduct(const Vector3D& vector);
    Vector3D vectorProduct(const Vector3D& vector);
    Vector3D crossProduct(const Vector3D& vector);
    Vector3D direction();
    void clear();
};

Vector3D tripleProduct(Vector3D a, Vector3D b, Vector3D c);

#endif
