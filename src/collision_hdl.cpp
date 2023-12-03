#include "collision_hdl.hpp"
#include "shape.hpp"

void 
COLLISION_HDL::addParticle(SHAPE* s)
{
    shapePool.insert(s);
}

void 
COLLISION_HDL::removeParticle(SHAPE* s)
{
    shapePool.erase(s);
}

void 
COLLISION_HDL::collisionHDL(SHAPE* s1, SHAPE* s2)
{
    VECTOR v1;
    VECTOR v2;

    float e1 = s1->getElasticity();
    float e2 = s2->getElasticity();

    VECTOR v1i = s1->getVelocity();
    VECTOR v2i = s2->getVelocity();

    v1 = e1*v1i + (1 - e1)* (v1i - (2*s2->getMass()/(s1->getMass() - s2->getMass()))*
        s1->normalize());

    v2 = e2*v2i + (1 - e2)* (v2i - (2*s1->getMass()/(s2->getMass() - s1->getMass()))*
        s2->normalize());

    p1->setVelocity(v1*-1);
    p2->setVelocity(v2*-1);
}

void 
COLLISION_HDL::collisionHDL(SHAPE* s)
{
    for(auto it : shapePool)
        collisionHDL(s,it);
}