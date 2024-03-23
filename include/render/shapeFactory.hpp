#ifndef __SHAPE_FACTORY__
#define __SHAPE_FACTORY__

#include <iostream>
#include "render/shape.hpp"

enum class ShapeType
{
    circle,
    rect
};

class ShapeFactory
{
public:
    static SHAPE* createShape(ShapeType type)
    {
        SHAPE* s;
        switch (type)
        {
        case ShapeType::circle:
            s = new CIRCLE();
            break;
        
        default:
            s = new RECTANGLE();
            break;
        }

        return s;
    }
};

#endif