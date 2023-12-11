#include "collision_hdl.hpp"
#include "shape.hpp"

bool 
COLLISION_HDL::isCollide(CIRCLE* circle, RECTANGLE* rect)
{
    if(circle->ismoving() | rect->ismoving())
    {

    }
}

bool 
COLLISION_HDL::isCollide(CIRCLE* circle_1, CIRCLE* circle_2)
{
    if(circle_1->ismoving() | circle_2->ismoving())
    {

    }
}

bool 
COLLISION_HDL::isCollide(RECTANGLE* rect_1, RECTANGLE* rect_2)
{
    if(rect_1->ismoving() | rect_2->ismoving())
    {

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
