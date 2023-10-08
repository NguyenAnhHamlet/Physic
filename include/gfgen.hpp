#ifndef __GFGEN__
#define __GFGEN__

#include<iostream>
#include<cmath>
#include<utility>
#include<vector>
#include "particle.hpp"
#include "pfgen.hpp"

class GFGEN: public PFGEN
{
    VECTOR gravity;

public:
    virtual void updateForce(PARTICLE* particle, float duration);

}

#endif