#ifndef __PFGEN__
#define __PFGEN__

#include<iostream>
#include<cmath>
#include<utility>
#include<vector>
#include<ctime>

/**
 * Interface
 * Other class use this as a base class and define its own method
 * for updateForce
*/

class PARTICLE;
class FORCE_VISITOR;

class PFGEN
{

public:
    virtual void visitUpdateForce(FORCE_VISITOR* vis, 
                                PARTICLE* particle, 
                                float duration) = 0;

    /**
     * Other class inherits from this interface must override this
     * method.
     * Use to calculate and update the force applies uppon particle
    */
    virtual void updateForce(PARTICLE* particle, float duration) = 0;
};

#endif
