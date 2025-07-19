#ifndef __PARTICLE_DRAG__
#define __PARTICLE_DRAG__

#include <iostream>
#include <cmath>
#include <assert.h>
#include <cstdlib>
#include "force/pfgen.hpp"
#include "common/common.hpp"

class PARTICLE;
class PFGEN;
class Vector3D;
class SHAPE;

class PARTICLE_DRAG: public PFGEN
{
    float dragCoeff;
    float density;

public:
    // PARTICLE_DRAG();
    /**
     *  TODO: Stop using magic number like this, quite confusing
     */
    PARTICLE_DRAG(float _dragCoeff =convertCM(70), float _density = convertCM(122.5));

    void setDragCoeff(float _dragCoeff);
    void setDensity(float _density);

    /**
     * Calculate the drag force generated from drag coeficent
     * and the velocity of this particle
     *
     * The velocity of course changes over time due to the change
     * in acceleration through the change in force which applied
     * upon itself. The problem is using integration can not
     * give out an equation to update the position of this particle
     * given the drag force.
     *
     * Drag force depends upon velocity, velocity depends upon acceleration
     * Acceleration depends upon Force. A vicious cycle.
     *
     * The only way i can think of is just calculate the drag force at
     * this very moment, then calculate the acceleration at this moment
     * to calculate velocity. Then update the position by that velocity
     * and given period of time. Just need to reduce the period of time
     * with which position of particle use to update as much as possible,
     * this way we can make it look as natual.
    */
    virtual void updateForce(SHAPE* shape, float duration ) override;

    // virtual void visitUpdateForce(PARTICLE* particle, 
    //                             float duration) override;
};

#endif
