#ifndef __COLLISION_HDL__
#define __COLLISION_HDL__

#include <set>

class SHAPE;

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
    std::set<SHAPE*> shapePool;

public:
    void addParticle(SHAPE* s);
    void removeParticle(SHAPE* s);

    /**
     * Handle the collistion between 2 particles
     * p1 and p2
    */
    void collisionHDL(SHAPE* s1, SHAPE* s2);
    void collisionHDL(SHAPE* s);
};

#endif