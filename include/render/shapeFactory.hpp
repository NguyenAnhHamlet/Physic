#ifndef __SHAPE_FACTORY__
#define __SHAPE_FACTORY__

#include <iostream>
#include "render/shape.hpp"

/***
 * *****************************************************
 *      SHAPE factory
 * *****************************************************
*/

// It is quite anoyying when a shape needs to be created 
// in case a user click mouse. Of couse some sort of shape 
// could be created before the mouse is clicked and then 
// be added into the BVH tree but making it lie into a 
// buffer without knowing when it will be presented is 
// quite unerving. The best choice here is to create a 
// shape factory to create shape and use it. 

class ShapeFactory
{
public: 
    // two overload function, one for circle and another 
    // for rectangle
    static SHAPE* createShape(Vector3D& coor, COLOR* _color, 
                              unsigned int radius);
    static SHAPE* createShape(Vector3D& coor, COLOR* _color, 
                              unsigned int _w, unsigned int _h);
}; 

#endif