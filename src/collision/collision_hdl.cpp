#include "collision/collision_hdl.hpp"
#include "render/shape.hpp"
#include "common/common.hpp"
#include "base/Vector3D.hpp"
#include <list>
#include"gjk/gjk.hpp"

void
COLLISION_HDL::collisionHDL(SHAPE* s)
{
    for(auto it : *(get_shape_holder()->get_set_shape_holder()))
    {
        collisionHDL(s,it);
    }
}

void
COLLISION_HDL::collisionHDL(SHAPE* s1, SHAPE* s2, float COR)
{
    if(!s1 || !s2) 
        return ;

    if(isCollide(s1,s2))
    {
        float penetrationD = penetrationDepth(s1->getPos(),
                                              s2->getPos(),
                                              s1->getR(), 
                                              s2->getR());
        
        Vector3D penetrationV = penetrationVec(s1->getPos(),
                                             s2->getPos());

        float bufferFactor = 0.1f;
        
        s1->setPos(s1->getPos() - penetrationV * penetrationD * 0.5);
        s2->setPos(s2->getPos() + penetrationV * penetrationD * 0.5);

        float m1 = s1->getMass();
        float m2 = s2->getMass();

        Vector3D v1 = s1->getVelocity();
        Vector3D v2 = s2->getVelocity();

        Vector3D* c1 = s1->getCenter();
        Vector3D* c2 = s2->getCenter();

        Vector3D delta_v1 = (v1 - v2) * COR;
        Vector3D delta_v2 = (v2 - v1) * COR;
        Vector3D delta_c1 = *c1 - *c2;
        Vector3D delta_c2 = *c2 - *c1;

        float scalar_term1 = delta_v1.scalarProduct(delta_c1) / pow(delta_c1.magnitude(), 2);
        float scalar_term2 = delta_v2.scalarProduct(delta_c2) / pow(delta_c2.magnitude(), 2);
        Vector3D v_fn1 = v1 - delta_c1 * ((2 * m2 / (m1 + m2)) * scalar_term1) ;
        Vector3D v_fn2 = v2 - delta_c2 * ((2 * m1 / (m1 + m2)) * scalar_term2);

        s1->setVelocity(v_fn1);
        s2->setVelocity(v_fn2);
    }
}

shape_holder* 
COLLISION_HDL::get_shape_holder() const
{
    return _shape_holder;
}

void
shape_holder::addShape(SHAPE* s)
{
    _set_shape_holder->insert(s);
}

void 
shape_holder::removeShape(SHAPE* s)
{
    _set_shape_holder->erase(s);
}

set_shape_holder*
shape_holder::get_set_shape_holder() const
{
    return _set_shape_holder;
}

float penetrationDepth(Vector3D pos1, Vector3D pos2, float r1, float r2 )
{
    Vector3D relativePosition = pos2 - pos1;
    float distance = relativePosition.magnitude();
    float penetrationDepth = std::max(0.0f, r1 + r2 - distance);
    return penetrationDepth;
}

Vector3D penetrationVec(Vector3D pos1, Vector3D pos2)
{
    Vector3D relativePosition = pos2 - pos1;
    float distance = relativePosition.magnitude();
    Vector3D penetrationVector3D = (distance > 0) ? relativePosition.normalize() : Vector3D(0, 0, 0);
    return penetrationVector3D;
}

bool
COLLISION_HDL::isCollide(SHAPE* s1, SHAPE* s2)
{
    std::vector<Vector3D> vertices;
    Vector3D direction;
    while(1)
        {
            switch (evolveSimplex(s1, s2, vertices, direction))
            {
                case EvolveResult::NoIntersection:
                    return 0;
                
                case EvolveResult::FoundIntersection:
                    return 1;

                default:
                    break;
            }
        }

    // there is problem happen 
    return -1;
}
