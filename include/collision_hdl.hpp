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

    shape_holder* _shape_holder;
public:
    shape_holder* get_shape_holder() const ;

    /**
     * User put the shape in, collision_hdl will be responsible 
     * for checking colision of all object inside shape_holder
     * and handle it
    */
    void collisionHDL(CIRCLE* circle);
    void collisionHDL(RECTANGLE* rect);

    static bool isCollide(CIRCLE* circle, RECTANGLE* rect);
    static bool isCollide(CIRCLE* circle_1, CIRCLE* circle_2);
    static bool isCollide(RECTANGLE* rect_1, RECTANGLE* rect_2);

    static void collisionHDL(SHAPE* s1, SHAPE* s2);
    static void collisionHDL(CIRCLE* circle, RECTANGLE* rect);
    static void collisionHDL(CIRCLE* circle_1, CIRCLE* circle_2);
    static void collisionHDL(RECTANGLE* rect_1, RECTANGLE* rect_2);
};

#endif