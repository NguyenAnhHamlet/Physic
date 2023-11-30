#ifndef __COLLISION_HDL__
#define __COLLISION_HDL__

#include "particle.hpp"
#include <set>

/**
 * Handle the collsion between 2 particle
 * 
 * This class have a set with value is pointer 
 * to such particle
 * 
 * User can create the instance of this class then 
 * use it for 1 job, handle the collsion of both 
 * particle. Either it be elastic, inelastic, movable,
 * unmovable.
 * 
*/
class COLLISION_HDL
{
    std::set<PARTICLE*> particlePool;

public:
    void addParticle(PARTICLE* particle);
    void removeParticle(PARTICLE* particle);
    void collisionHDL(PARTICLE* p1, PARTICLE* p2);
    void collisionHDL(PARTICLE* particle);
};

#endif