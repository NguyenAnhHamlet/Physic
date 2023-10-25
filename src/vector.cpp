#include "vector.hpp"

VECTOR::VECTOR(float x, float y, float z) : x(x), y(y), z(z)
{}

void 
VECTOR::operator=(const VECTOR& vector)
{
    this->x = vector.x;
    this->y = vector.y;
    this->z = vector.z;
}

VECTOR 
VECTOR::invert()
{
    return VECTOR(x*-1,y*-1,z*-1);
}

VECTOR 
VECTOR::operator+(const VECTOR& vector)
{
    return VECTOR(x + vector.x, y + vector.y, z + vector.z);
}

VECTOR 
VECTOR::operator-(const VECTOR& vector)
{
    return VECTOR(x - vector.x, y - vector.y, z - vector.z);
}

VECTOR 
VECTOR::operator*( float number)
{
    return VECTOR(number * x, number * y, number * z);
}

float 
VECTOR::magnitude()
{
    return sqrt(x*x + y*y + z*z);
}

VECTOR 
VECTOR::normalize()
{
    float mag = magnitude();

    if(mag > 0)
    {
        return (*this) / mag;
    }
    return VECTOR(0,0,0);
}

VECTOR 
VECTOR::operator/(float number)
{
    return VECTOR(x/number, y/number, z/number);
}

VECTOR 
VECTOR::operator/(VECTOR vector)
{
    float scalar1 = scalarProduct(vector);
    float scalar2 = vector.scalarProduct(vector);
    return vector * scalar1/scalar2;
}

VECTOR 
VECTOR::operator*(const VECTOR& vector)
{
    return VECTOR(x*vector.x, y*vector.y, z*vector.z);
}

float 
VECTOR::scalarProduct(const VECTOR& vector)
{
    return (x* vector.x + y * vector.y + z * vector.z);
}

VECTOR 
VECTOR::componentProduct(const VECTOR& vector)
{
    return VECTOR(x* vector.x, y* vector.y, z* vector.z);
}

VECTOR 
VECTOR::vectorProduct(const VECTOR& vector)
{
    return VECTOR(y*vector.z - z* vector.y,
                z*vector.x - x*vector.z,
                x*vector.y - y* vector.x);
}

VECTOR 
VECTOR::direction()
{
    return (*this) / this->magnitude();
}

void 
VECTOR::clear()
{
    this->x =0;
    this->y =0;
    this->z =0;
}
