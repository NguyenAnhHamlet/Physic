#ifndef __COLLISION_HDL__
#define __COLLISION_HDL__

#include <set>

class SHAPE;

/**
 * Handle the collsion between a set of shape
 * 
 * This class have a set with value is pointer 
 * to such shape
 * 
 * User can create the instance of this class then 
 * use it for 1 job, handle the collsion of all particle
 * inside a set shapePool.
 * 
*/
class COLLISION_HDL
{
    std::set<SHAPE*> shapePool;

public:
    void addParticle(SHAPE* s);
    void removeParticle(SHAPE* s);

    /**
     * Handle the collistion between shape
     * and all shape inside shapePool
    */
    // void collisionHDL(SHAPE* s1, SHAPE* s2);
    void collisionHDL(SHAPE* s);
};

#endif