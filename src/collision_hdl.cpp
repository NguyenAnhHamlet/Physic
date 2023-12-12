#include "collision_hdl.hpp"
#include "shape.hpp"
#include "common.hpp"

bool 
COLLISION_HDL::isCollide(CIRCLE* circle, RECTANGLE* rect)
{
    if(circle->ismoving() | rect->ismoving())
    {
        float x = abs(circle->getCenter().x - rect->getCenter().x);
        float y = abs(circle->getCenter().y - rect->getCenter().y);

        float h = hypotenuse(x,y);
        std::vector<VECTOR*> points = rect->getPoints();

        // axis checking 
        if( h <= rect->getAxisL() + circle->getR())
        {
            for(auto p : points)
            {
                if(collinearPoints(circle->getCenter(), rect->getCenter(), p))
                    return true;
            }
        }

        // side checking

        // possible collision on top or at the bottom
        if(circle->getCenter().x + circle->getR() > points[0] && 
                circle->getCenter().x - circle->getR() < points[1] && 
                h >= rect->getRect().y /2 + circle->getR())

            return true;

        // possible collision at the side
        if(circle->getCenter().y + circle->getR()> points[1] && 
                circle->getCenter().y  circle->getR() < points[3] && 
                h >= rect->getRect().x /2 + circle->getR())
                
            return true;

    }

    return false;
}

bool 
COLLISION_HDL::isCollide(CIRCLE* circle_1, CIRCLE* circle_2)
{
    if(circle_1->ismoving() | circle_2->ismoving())
    {
        float x = abs(circle_1->getCenter().x - circle_2->getCenter().x);
        float y = abs(circle_1->getCenter().y - circle_2->getCenter().y);

        float h = hypotenuse(x,y);
        if(h <= circle_1->getR() + circle_2->getR()) 
            return true;
    }

    return false;
}

bool 
COLLISION_HDL::isCollide(RECTANGLE* rect_1, RECTANGLE* rect_2)
{
    if(rect_1->ismoving() | rect_2->ismoving())
    {
        // possible collision on top or at the bottom
        if(rect_1->getCenter().x + rect_1->getRect().x /2 > points[0] && 
                circle->getCenter().x - rect_1->getRect().x /2 < points[1])
            return true;

        // possible collision at the side
        if(circle->getCenter().y + rect_1->getRect().y /2> points[1] && 
                circle->getCenter().y  circle->getR().y /2 < points[3])
            return true;
        
        return false;
    }
}

void
COLLISION_HDL::collisionHDL(CIRCLE* circle)
{
    for(auto it : _set_shape_holder)
    {
        if(static_cast<CIRCLE*>(it)) 
            collisionHDL(circle,static_cast<CIRCLE*>(it));
        else
            collisionHDL(circle, static_cast<RECTANGLE*>(it)); 
    }
}

void
COLLISION_HDL::collisionHDL(RECTANGLE* rect)
{
    for(auto it : _set_shape_holder)
    {
        if(static_cast<CIRCLE*>(it)) 
            collisionHDL(static_cast<CIRCLE*>(it),rect);
        else
            collisionHDL(static_cast<RECTANGLE*>(it), rect); 
    }
}

void
COLLISION_HDL::collisionHDL(CIRCLE* circle, RECTANGLE* rect)
{
    if(isCollide(circle,rect))
    {

    }
}

void 
COLLISION_HDL::collisionHDL(CIRCLE* circle_1, CIRCLE* circle_2)
{
    if(isCollide(circle_1,circle_2))
    {
        
    }
}

void
COLLISION_HDL::collisionHDL(RECTANGLE* rect_1, RECTANGLE* rect_2)
{
    if(isCollide(rect_1,rect_2))
    {
        
    }    
}
