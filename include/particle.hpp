#ifndef __PARTICLE__
#define __PARTICLE__

#include <iostream>
#include <cmath>
#include "vector.hpp"
#include <assert.h>
#include "gfgen.hpp"
#include "particleDrag.hpp"

class PARTICLE
{

public:
    // position of the particle in space
    VECTOR pos;

    // velocity of this particle in space
    VECTOR velocity;

    // acceleration of this particle in space
    VECTOR acceleration;

    /*
    /   this value is used to remove the energy added
    /   through numerical instability
    /   Default is 0.99
    */
    float damping;

    /**
     *  use inverseMass to store the value of 1/mass
     *  this make the integration less expensive
    **/
    float inverseMass;
    float mass;

    /**
     * Speed is different from velocity, it doesnt involes
     * 3D space like velocity and is just a magnitude of 
     * vector velocity
     * 
     * Default is set to magnitude of velocity vector
    */
    float speed;

    /**
     * Total force applied uppon this particle
    */
    VECTOR forceAccum;

    // gravity applied uppon this particle
    GFGEN gravityForce;

    // drag force applied upon this particle
    PARTICLE_DRAG dragForce;

    /**
     * TIMER object to keep up with time for multiple
     * purposes
    */
    TIMER timer;

    // default constructor to prevent core dump
    PARTICLE() : damping(0), inverseMass(0), damping(0.99), mass(0)
                {};

    // user can determine these var
    PARTICLE(float _damping, float _inverseMass, float _gravity
            ,VECTOR _pos, VECTOR _velocity, VECTOR _acceleration )
            :damping(_damping), inverseMass(_inverseMass)
            ,pos(_pos), velocity(_velocity), acceleration(_acceleration)
        {};

    float getMass()
        { return mass};

    // use this function after object being created 
    void init();

    /**
     *  update the position of this particle in a given time
     *  without acceleration and force
    */
    void posUpdate(VECTOR velocity, float duration);

    //this one update the position of this particle with acceleration and force
    void posUpdate(VECTOR velocity, VECTOR acceleration,
                    float duration);

    /**
     * Particle under the effect of gravity has projectile property 
     * and to create a realistic effect of a projectile, use 
     * the formula:
     * g' = g/s
    */

    //add force onto forceAccum
    void addForce(const VECTOR& force);
    
    // Get velocity of this particle through force
    VECTOR getAcceleration(const VECTOR& force);

    // set the gravity for this particle in case one wanna use 
    void setGravity(GFGEN& _gravityForce);

    // set the drag force for this particle 
    void setDrag(PARTICLE_DRAG& _dragForce);

    void clearForce();
 
    /**
     * Get velocity from force in a given time 
     * We mainly use velocity with force eventhough 
     * the equation F = m*a help to calculate directly 
     * acceleration, mainly due to the drag force is 
     * directly related to velocity, if the velocity doesn't 
     * change, the particle will move forever.
     * 
     * By updating the position based mainly on velocity 
     * The acceleration is, in this particle is supposed to 
     * be initial and intemidiate value, even though it sounds 
     * contradictory since the force actually affect the acceleration of 
     * a particle, but doing it that way will make it harder 
     * to work with. Instead just update the velocity of this 
     * particle based on acceleration and we can manipulate the 
     * behavior of such particle easier
     * 
     * v' = v + integration of a(dt) = v + at
    */
    VECTOR getVelocity(const VECTOR& force, float duration);
};

#endif
