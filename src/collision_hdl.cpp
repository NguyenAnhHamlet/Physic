#include "collision_hdl.hpp"
#include "shape.hpp"
#include "common.hpp"
#include "vector.hpp"

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
    VECTOR space = (circle_1->getPos() - circle_2->getPos());
    float h = space.magnitude();

    if(h <= circle_1->getR() + circle_2->getR()) 
        return true;
    
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
COLLISION_HDL::collisionHDL(CIRCLE* circle, RECTANGLE* rect, float COR)
{
    if(!circle || !rect) 
        return ;

    if(isCollide(circle,rect))
    {
        // float penetrationD = penetrationDepth(  circle->getPos(),
        //                                         rect->getPos(),
        //                                         circle->getR(),
        //                                         rect->getR());
        
        // VECTOR penetrationV = penetrationVec(circle->getPos(),
        //                                      rect->getPos());
        
        // circle->setPos(circle->getPos() + penetrationV * 0.5 * penetrationD);
        // rect->setPos(rect->getPos() + penetrationV * 0.5 * penetrationD);

        float m1 = circle->getMass();
        float m2 = rect->getMass();

        VECTOR v1 = circle->getVelocity();
        VECTOR v2 = rect->getVelocity();

        VECTOR* c1 = circle->getCenter();
        VECTOR* c2 = rect->getCenter();

        VECTOR delta_v1 = (v1 - v2) * COR;
        VECTOR delta_v2 = (v2 - v1) * COR;
        VECTOR delta_c1 = *c1 - *c2;
        VECTOR delta_c2 = *c2 - *c1;

        float scalar_term1 = delta_v1.scalarProduct(delta_c1) / pow(delta_c1.magnitude(), 2);
        float scalar_term2 = delta_v2.scalarProduct(delta_c2) / pow(delta_c2.magnitude(), 2);
        VECTOR v_fn1 = v1 - delta_c1 * ((2 * m2 / (m1 + m2)) * scalar_term1) ;
        VECTOR v_fn2 = v2 - delta_c2 * ((2 * m1 / (m1 + m2)) * scalar_term2);

        circle->setVelocity(v_fn1);
        rect->setVelocity(v_fn2);
    }
}

void 
COLLISION_HDL::collisionHDL(CIRCLE* circle_1, CIRCLE* circle_2, float COR)
{
    if(!circle_1 || !circle_2) 
        return ;

    if(isCollide(circle_1,circle_2))
    {
        float penetrationD = penetrationDepth(circle_1->getPos(),
                                              circle_2->getPos(),
                                              circle_1->getR(),
                                              circle_2->getR());
        
        VECTOR penetrationV = penetrationVec(circle_1->getPos(),
                                             circle_2->getPos());

                                             float bufferFactor = 0.1f;
        
        circle_1->setPos(circle_1->getPos() - penetrationV * penetrationD * 0.5);
        circle_2->setPos(circle_2->getPos() + penetrationV * penetrationD * 0.5);

        float m1 = circle_1->getMass();
        float m2 = circle_2->getMass();

        VECTOR v1 = circle_1->getVelocity();
        VECTOR v2 = circle_2->getVelocity();

        VECTOR* c1 = circle_1->getCenter();
        VECTOR* c2 = circle_2->getCenter();

        VECTOR delta_v1 = (v1 - v2) * COR;
        VECTOR delta_v2 = (v2 - v1) * COR;
        VECTOR delta_c1 = *c1 - *c2;
        VECTOR delta_c2 = *c2 - *c1;

        float scalar_term1 = delta_v1.scalarProduct(delta_c1) / pow(delta_c1.magnitude(), 2);
        float scalar_term2 = delta_v2.scalarProduct(delta_c2) / pow(delta_c2.magnitude(), 2);
        VECTOR v_fn1 = v1 - delta_c1 * ((2 * m2 / (m1 + m2)) * scalar_term1) ;
        VECTOR v_fn2 = v2 - delta_c2 * ((2 * m1 / (m1 + m2)) * scalar_term2);

        circle_1->setVelocity(v_fn1);
        circle_2->setVelocity(v_fn2);
    }
}

void
COLLISION_HDL::collisionHDL(RECTANGLE* rect_1, RECTANGLE* rect_2, float COR)
{
    if(!rect_1 || !rect_2) 
        return ;

    if(isCollide(rect_1,rect_2))
    {
        // float penetrationD = penetrationDepth(rect_1->getPos(),
        //                                       rect_2->getPos(),
        //                                       rect_1->getR(),
        //                                       rect_2->getR());
        
        // VECTOR penetrationV = penetrationVec(rect_1->getPos(),
        //                                      rect_2->getPos());
        
        // rect_1->setPos(rect_1->getPos() + penetrationV * 0.5 * penetrationD);
        // rect_2->setPos(rect_2->getPos() + penetrationV * 0.5 * penetrationD);

        float m1 = rect_1->getMass();
        float m2 = rect_2->getMass();

        VECTOR v1 = rect_1->getVelocity();
        VECTOR v2 = rect_2->getVelocity();

        VECTOR* c1 = rect_1->getCenter();
        VECTOR* c2 = rect_2->getCenter();

        VECTOR delta_v1 = (v1 - v2) * COR ;
        VECTOR delta_v2 = (v2 - v1) * COR;
        VECTOR delta_c1 = *c1 - *c2;
        VECTOR delta_c2 = *c2 - *c1;
        
        float scalar_term1 = delta_v1.scalarProduct(delta_c1) / pow(delta_c1.magnitude(), 2);
        float scalar_term2 = delta_v2.scalarProduct(delta_c2) / pow(delta_c2.magnitude(), 2);
        VECTOR v_fn1 = v1 - delta_c1 * ((2 * m2 / (m1 + m2)) * scalar_term1) ;
        VECTOR v_fn2 = v2 - delta_c2 * ((2 * m1 / (m1 + m2)) * scalar_term2);

        rect_1->setVelocity(v_fn1);
        rect_2->setVelocity(v_fn2);
    }
}

void
COLLISION_HDL::collisionHDL(SHAPE* s1, SHAPE* s2, float COR)
{
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

float penetrationDepth(VECTOR pos1, VECTOR pos2, float r1, float r2 )
{
    VECTOR relativePosition = pos2 - pos1;
    float distance = relativePosition.magnitude();
    float penetrationDepth = std::max(0.0f, r1 + r2 - distance);
    return penetrationDepth;
}

VECTOR penetrationVec(VECTOR pos1, VECTOR pos2)
{
    VECTOR relativePosition = pos2 - pos1;
    float distance = relativePosition.magnitude();
    VECTOR penetrationVector = (distance > 0) ? relativePosition.normalize() : VECTOR(0, 0, 0);
    return penetrationVector;
}
