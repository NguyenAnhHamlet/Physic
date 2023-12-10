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

// void 
// COLLISION_HDL::collisionHDL(SHAPE* s1, SHAPE* s2)
// {
//     VECTOR v1;
//     VECTOR v2;

//     float e1 = s1->getElasticity();
//     float e2 = s2->getElasticity();

//     VECTOR v1i = s1->getVelocity();
//     VECTOR v2i = s2->getVelocity();

//     // if both got infinite mass , do nothing
//     if(!(s1->getInverseMass() | s2->getInverseMass())) 
//         return;

//     /**
//      * In case 1 got infinite mass then only 
//      * calculate the velocity of the non-infinite 
//      * mass one. 
//      * 
//      * With non-infinite mass :
//      * v1 = e1*v1i + (1 - e1) *(v1i - (2*m1 / m1 - m2) * (v1i - v2i) * r)
//      * with r is normalize vector value of center mass vector
//      * 
//      * With infinite mass since (2*m1 / m1 - m2) = 0 then
//      * v1 = e2*v2i + (1 - e2) * v2i
//     */
//     if(!s1->getInverseMass())
//     {
//         v1 = v1i;
//         v2 = e1*v1i + (1 - e1) * v1i;
//     }
//     else if(!s2->getInverseMass())
//     {
//         v2 = v2i;
//         v1 = e2*v2i + (1 - e2) * v2i;
//     }
//     else
//     {
//         v1 = e1*v1i + (1 - e1)* (v1i - ((2*s2->getMass()/(s1->getMass() - s2->getMass()))*
//             (v1i - v2i) * s1->normalize()));

//         v2 = e2*v2i + (1 - e2)* (v2i - ((2*s1->getMass()/(s2->getMass() - s1->getMass()))*
//             (v2i - v1i) * s2->normalize()));
//     }

//     // set the final velocity of both shape
//     s1->setVelocity(v1);
//     s2->setVelocity(v2);
// }
