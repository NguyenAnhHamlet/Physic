#include "collision_hdl.hpp"
#include "shape.hpp"
#include "common.hpp"

bool 
COLLISION_HDL::isCollide(CIRCLE* circle, RECTANGLE* rect)
{
    if(circle->ismoving() | rect->ismoving())
    {
        float x = abs(circle->getCenter()->x - rect->getCenter()->x);
        float y = abs(circle->getCenter()->y - rect->getCenter()->y);

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
        if(circle->getCenter()->x + circle->getR() > points[0]->x && 
                circle->getCenter()->x - circle->getR() < points[1]->x && 
                h >= rect->getRect()->y /2 + circle->getR())

            return true;

        // possible collision at the side
        if(circle->getCenter()->y + circle->getR()> points[1]->y && 
                circle->getCenter()->y - circle->getR() < points[3]->y && 
                h >= rect->getRect()->x /2 + circle->getR())
                
            return true;

    }

    return false;
}

bool 
COLLISION_HDL::isCollide(CIRCLE* circle_1, CIRCLE* circle_2)
{
    if(circle_1->ismoving() | circle_2->ismoving())
    {
        float x = abs(circle_1->getCenter()->x - circle_2->getCenter()->x);
        float y = abs(circle_1->getCenter()->y - circle_2->getCenter()->y);

        float h = hypotenuse(x,y);
        if(h <= circle_1->getR() + circle_2->getR()) 
            return true;
    }

    return false;
}

bool 
COLLISION_HDL::isCollide(RECTANGLE* rect_1, RECTANGLE* rect_2)
{
    std::vector<VECTOR*> p1 = rect_1->getPoints();
    std::vector<VECTOR*> p2 = rect_2->getPoints();
   
    // If one rectangle is on left side of other
    if (p1[1]->x > p2[0]->x || p2[1]->x > p1[0]->x)
        return false;
 
    // If one rectangle is above other
    if (p1[1]->y > p2[0]->y || p2[1]->y > p1[0]->y)
        return false;
 
    return true;
}

void
COLLISION_HDL::collisionHDL(CIRCLE* circle)
{
    for(auto it : *(get_shape_holder()->get_set_shape_holder()))
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
    for(auto it : *(get_shape_holder()->get_set_shape_holder()))
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
    // std::cout << rect << '\n';
    if(!circle || !rect) 
        return ;

    if(isCollide(circle,rect))
    {
        float m1 = circle->getMass();
        float m2 = rect->getMass();

        VECTOR v1 = circle->getVelocity();
        VECTOR v2 = rect->getVelocity();

        VECTOR* c1 = circle->getCenter();
        VECTOR* c2 = rect->getCenter();

        VECTOR delta_v = (v1 - v2);
        VECTOR delta_c = (*c1 - *c2);
        float scalar_term = delta_v.scalarProduct(delta_c) / pow(delta_c.magnitude(), 2);
        VECTOR v_fn1 = v1 - delta_c * ((2 * m2 / (m1 + m2)) * scalar_term) ;
        VECTOR v_fn2 = v2 - delta_c * ((2 * m1 / (m1 + m2)) * scalar_term);

        circle->setVelocity(v_fn1);
        rect->setVelocity(v_fn2);
    }
}

void 
COLLISION_HDL::collisionHDL(CIRCLE* circle_1, CIRCLE* circle_2)
{
    if(!circle_1 || !circle_2) 
        return ;

    if(isCollide(circle_1,circle_2))
    {
        float m1 = circle_1->getMass();
        float m2 = circle_2->getMass();

        VECTOR v1 = circle_1->getVelocity();
        VECTOR v2 = circle_2->getVelocity();

        VECTOR* c1 = circle_1->getCenter();
        VECTOR* c2 = circle_2->getCenter();

        VECTOR delta_v = (v1 - v2);
        VECTOR delta_c = (*c1 - *c2);
        float scalar_term = delta_v.scalarProduct(delta_c) / pow(delta_c.magnitude(), 2);
        VECTOR v_fn1 = v1 - delta_c * ((2 * m2 / (m1 + m2)) * scalar_term) ;
        VECTOR v_fn2 = v2 - delta_c * ((2 * m1 / (m1 + m2)) * scalar_term);

        circle_1->setVelocity(v_fn1);
        circle_2->setVelocity(v_fn2);
    }
}

void
COLLISION_HDL::collisionHDL(RECTANGLE* rect_1, RECTANGLE* rect_2)
{
    if(!rect_1 || !rect_2) 
        return ;

    if(isCollide(rect_1,rect_2))
    {
        float m1 = rect_1->getMass();
        float m2 = rect_2->getMass();

        VECTOR v1 = rect_1->getVelocity();
        VECTOR v2 = rect_2->getVelocity();

        VECTOR* c1 = rect_1->getCenter();
        VECTOR* c2 = rect_2->getCenter();

        VECTOR delta_v = (v1 - v2);
        VECTOR delta_c = (*c1 - *c2);
        float scalar_term = delta_v.scalarProduct(delta_c) / pow(delta_c.magnitude(), 2);
        VECTOR v_fn1 = v1 - delta_c * ((2 * m2 / (m1 + m2)) * scalar_term) ;
        VECTOR v_fn2 = v2 - delta_c * ((2 * m1 / (m1 + m2)) * scalar_term);

        rect_1->setVelocity(v_fn1);
        rect_2->setVelocity(v_fn2);
    }
}

void
COLLISION_HDL::collisionHDL(SHAPE* s1, SHAPE* s2)
{
    std::cout << "COLLISION" << '\n';
    while(1)
    {
        
    }
    collisionHDL(dynamic_cast<CIRCLE*>(s1), dynamic_cast<CIRCLE*>(s2));
    collisionHDL(dynamic_cast<CIRCLE*>(s1), dynamic_cast<RECTANGLE*>(s2));
    collisionHDL(dynamic_cast<RECTANGLE*>(s1), dynamic_cast<RECTANGLE*>(s2));
    collisionHDL(dynamic_cast<CIRCLE*>(s2), dynamic_cast<RECTANGLE*>(s1));
}

shape_holder* 
COLLISION_HDL::get_shape_holder() const
{
    return _shape_holder;
}

void
shape_holder::addShape(SHAPE* s)
{

}

void 
shape_holder::removeShape(SHAPE* s)
{

}

set_shape_holder*
shape_holder::get_set_shape_holder() const
{
    return _set_shape_holder;
}
