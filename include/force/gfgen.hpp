#ifndef __GFGEN__
#define __GFGEN__

#include<iostream>
#include<cmath>
#include<utility>
#include<vector>
#include "force/pfgen.hpp"
#include "base/Vector3D.hpp"

class PARTICLE;
class PFGEN;
class Vector3D;
class SHAPE;

class GFGEN: public PFGEN
{   
    Vector3D gravity;
    GFGEN();
    static GFGEN* gfgen;

    // deleting copy constructor
    GFGEN(const GFGEN& gfgen)= delete; 

    // deleting assign operator
    GFGEN& operator=(const GFGEN&) = delete;

public:
    static GFGEN* getInstance()
    {
        if( !gfgen) gfgen = new GFGEN();
        return gfgen;
    }
    virtual void updateForce(SHAPE* shape, float duration) override;
};

#endif
