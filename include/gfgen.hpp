#ifndef __GFGEN__
#define __GFGEN__

#include<iostream>
#include<cmath>
#include<utility>
#include<vector>
#include "pfgen.hpp"
#include "vector.hpp"

class PARTICLE;
class PFGEN;
class VECTOR;

class GFGEN: public PFGEN
{   
    VECTOR gravity;

public:
    GFGEN();
    virtual void updateForce(PARTICLE* particle, float duration) override;

    virtual void visitUpdateForce(FORCE_VISITOR* vis, 
                            PARTICLE* particle, 
                            float duration) override;
};

#endif
