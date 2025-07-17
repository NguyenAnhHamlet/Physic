#ifndef __POINT2D__
#define __POINT2D__

// point2D is just a 2D vector, this is used by Bounds2D to help 
// create a bound that hold some important component including
// pMin, pMax and centroid that used for splitting and creating 
// bound around a primitive/SHAPE

#include <iostream>
#include <utility>

class point2D
{

public:
    float x, y;  
    point2D() : x(0), y(0){}
    point2D(float _x, float _y)
            : x(_x), y(_y){}

    void operator=(const point2D& p)
    {
        x = p.x;
        y = p.y;
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    void setX(int _x)
    {
        x = _x;
    }

    void setY(int _y)
    {
        y = _y;
    }

};


#endif