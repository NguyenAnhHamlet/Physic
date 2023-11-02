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
    GFGEN();
    static GFGEN* gfgen;

    // deleting copy constructor
    GFGEN(const GFGEN& gfgen)= delete; 

    // deleting assign operator
    GFGEN& operator=(const GFGEN&) = delete;

public:
    static GFGEN* getInstance();
    virtual void updateForce(PARTICLE* particle, float duration) override;

    virtual void visitUpdateForce(FORCE_VISITOR* vis, 
                            PARTICLE* particle, 
                            float duration) override;
};

#endif
