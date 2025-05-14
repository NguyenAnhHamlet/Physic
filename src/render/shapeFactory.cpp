#include "render/shape.hpp"
#include "render/renderer.hpp"
#include "common/common.hpp"
#include <cmath>
#include "collision/collision_hdl.hpp"
#include <math.h>
#include "bvh/point2D.hpp"
#include "base/Vector3D.hpp"
#include "render/shapeFactory.hpp"
#include "render/shape.hpp"

SHAPE*
ShapeFactory::createShape(Vector3D& coor, COLOR* _color, 
                          unsigned int radius)
{
    SHAPE* ret = new CIRCLE(_color, radius);
    ret->setPos(coor);
    return ret;
}

SHAPE*
ShapeFactory::createShape(Vector3D& coor, COLOR* _color, 
                          unsigned int _w, unsigned int _h)
{
    SHAPE* ret = new RECTANGLE(_color, _w, _h);
    ret->setPos(coor);
    return ret;
}