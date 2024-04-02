#include "base/Vector3D.hpp"

<<<<<<< HEAD
Vector3D::Vector3D(float x, float y, float z) : 
            x(x), y(y), z(z)
=======
Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z)
>>>>>>> f643c6cccabf372d6914e417cd8a5ae3c37bb2a5
{}

void 
Vector3D::operator=(const Vector3D& vector)
{
    this->x = vector.x;
    this->y = vector.y;
    this->z = vector.z;
}

Vector3D 
Vector3D::invert()
{
    return Vector3D(x*-1,y*-1,z*-1);
}

Vector3D 
Vector3D::operator+(const Vector3D& vector)
{
    return Vector3D(x + vector.x, y + vector.y, z + vector.z);
}

Vector3D 
Vector3D::operator-(const Vector3D& vector)
{
    return Vector3D(x - vector.x, y - vector.y, z - vector.z);
}

Vector3D 
Vector3D::operator*( float number)
{
    return Vector3D(number * x, number * y, number * z);
}

float 
Vector3D::magnitude()
{
    return sqrt(x*x + y*y + z*z);
}

Vector3D 
Vector3D::normalize()
{
    float mag = magnitude();

    if(mag > 0)
    {
        return (*this) / mag;
    }
    return Vector3D(0,0,0);
}

Vector3D 
Vector3D::operator/(float number)
{
    return Vector3D(x/number, y/number, z/number);
}

Vector3D 
Vector3D::operator/(Vector3D vector)
{
    float scalar1 = scalarProduct(vector);
    float scalar2 = vector.scalarProduct(vector);
    return vector * scalar1/scalar2;
}

Vector3D 
Vector3D::operator*(const Vector3D& vector)
{
    return Vector3D(x*vector.x, y*vector.y, z*vector.z);
}

float 
Vector3D::scalarProduct(const Vector3D& vector)
{
    return (x* vector.x + y * vector.y + z * vector.z);
}

Vector3D 
Vector3D::componentProduct(const Vector3D& vector)
{
    return Vector3D(x* vector.x, y* vector.y, z* vector.z);
}

Vector3D 
Vector3D::vectorProduct(const Vector3D& vector)
{
    return Vector3D(y*vector.z - z* vector.y,
                z*vector.x - x*vector.z,
                x*vector.y - y* vector.x);
}

Vector3D 
Vector3D::direction()
{
    return (*this) / this->magnitude();
}

void 
Vector3D::clear()
{
    this->x =0;
    this->y =0;
    this->z =0;
}

Vector3D tripleProduct(Vector3D a, Vector3D b, Vector3D c)
{
  return a.vectorProduct(b.vectorProduct(c));
}

float 
Vector3D::dotProduct(const Vector3D& vector)
{
    return scalarProduct(vector);
}

Vector3D 
Vector3D::crossProduct(const Vector3D& vector)
{
    return vectorProduct(vector);
}