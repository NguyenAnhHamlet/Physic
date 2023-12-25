#ifndef __POINT2D__
#define __POINT2D__

#include <iostream>

class point2D
{
    float x, y;  

    point2D() : x(0), y(0){}
    point2D(float _x, float _y)
            : x(_x), y(_y){}

    void operator=(const point2D& _point2D)
    {
        x = _point2D.x;
        y = _point2D.y;
    }

    bool operator>(const point2D& _point2D)
    {
        if(x > _point2D.x) return true;
        if(x == _point2D.x && y > _point2D.y) return true;

        return false;
    }

    bool operator<(const point2D& _point2D)
    {
        if(x < _point2D.x) return true;
        if(x == _point2D.x && y < _point2D.y) return true;
        return false;
    }

    bool operator==(const point2D& _point2D)
    {
        if(x == _point2D.x && y == _point2D.y) return true;
        return false;
    }

};


#endif