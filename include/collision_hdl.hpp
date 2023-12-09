#ifndef __COLLISION_HDL__
#define __COLLISION_HDL__

#include <set>
#include <map>

class SHAPE;
class RECTANGLE;
class CIRCLE;
class shape_holder;

/***
 * *****************************************************
 *      COLLISION_HDL
 * *****************************************************
*/

/**
 * Handle the collsion between a set of shape
 * 
 * This class have a set with value is pointer 
 * to such shape
 * 
 * User can create the instance of this class then 
 * use it for 1 job, handle the collsion of all particle
 * inside a set shapePool.
 * 
*/
class COLLISION_HDL
{
    shape_holder _shape_holder;

public:
    shape_holder* get_shape_holder() const ;

    bool isCollide(CIRCLE* circle, RECTANGLE* rect);
    bool isCollide(CIRCLE* circle, CIRCLE* circle);
    bool isCollide(RECTANGLE* rect, RECTANGLE* rect);

    void collisionHDL(CIRCLE* circle, RECTANGLE* rect);
    void collisionHDL(CIRCLE* circle, CIRCLE* circle);
    void collisionHDL(RECTANGLE* rect, RECTANGLE* rect);
};

#endif