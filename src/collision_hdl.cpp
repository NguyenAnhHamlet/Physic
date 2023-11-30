#include "collision_hdl.hpp"

void 
COLLISION_HDL::addParticle(PARTICLE* particle)
{
    particlePool.insert(particle);
}

void 
COLLISION_HDL::removeParticle(PARTICLE* particle)
{
    particlePool.erase(particle);
}

void 
COLLISION_HDL::collisionHDL(PARTICLE* p1, PARTICLE* p2)
{

}

void 
COLLISION_HDL::collisionHDL(PARTICLE* particle)
{
    for(auto it : particlePool)
        collisionHDL(particle,it);
}