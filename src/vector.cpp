#include "vector.hpp"

VECTOR::VECTOR(float x, float y, float z) : x(x), y(y), z(z)
{}

VECTOR VECTOR::invert()
{
    return VECTOR(x*-1,y*-1,z*-1);
}

VECTOR VECTOR::add(const VECTOR& vector)
{
    return VECTOR(x + vector.x, y + vector.y, z + vector.z);
}

VECTOR VECTOR::substract(const VECTOR& vector)
{
    return VECTOR(x - vector.x, y - vector.y, z - vector.z);
}

VECTOR VECTOR::multiply( int number)
{
    return VECTOR(number * x, number * y, number * z);
}

float VECTOR::magnitude()
{
    return sqrt(x*x + y*y + z*z);
}

VECTOR VECTOR::normalize()
{
    float mag = magnitude();

    if(mag > 0)
    {
        return divide(mag);
    }
    return VECTOR(0,0,0);
}

VECTOR VECTOR::divide(int number)
{
    return VECTOR(x/number, y/number, z/number);
}

VECTOR VECTOR::divide(VECTOR vector)
{
    float scalar1 = scalarProduct(vector);
    float scalar2 = vector.scalarProduct(vector);
    return vector.multiply(scalar1/scalar2);
}

VECTOR VECTOR::multiply(const VECTOR& vector)
{
    return VECTOR(x*vector.x, y*vector.y, z*vector.z);
}

float VECTOR::scalarProduct(const VECTOR& vector)
{
    return (x* vector.x + y * vector.y + z * vector.z);
}

VECTOR VECTOR::componentProduct(const VECTOR& vector)
{
    return VECTOR(x* vector.x, y* vector.y, z* vector.z);
}

VECTOR VECTOR::vectorProduct(const VECTOR& vector)
{
    return VECTOR(y*vector.z - z* vector.y,
                z*vector.x - x*vector.z,
                x*vector.y - y* vector.x);
}

VECTOR VECTOR::direction()
{
    return (*this).divide(magnitude());
}

void VECTOR::clear()
{
    this->x =0;
    this->y =0;
    this->z =0;
}
