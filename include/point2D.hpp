#ifndef __POINT2D__
#define __POINT2D__

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

};


#endif