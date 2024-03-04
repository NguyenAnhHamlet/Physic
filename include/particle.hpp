#ifndef __PARTICLE__
#define __PARTICLE__

#include <iostream>
#include <cmath>
#include <assert.h>

#include "vector.hpp"
#include "gfgen.hpp"
#include "timer.hpp"
#include "particleDrag.hpp"
#include "common.hpp"

class GFGEN;
class PARTICLE_DRAG;
class VECTOR;
class TIMER;
class PARTICLE_FORCE_REGISTER;

class PARTICLE
{
protected:
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

    // degree of elasticity
    float elasticity;

public:
    std::thread* CountDown = NULL;
    /**
     * Total force applied uppon this particle
    */
    VECTOR forceAccum;

    TIMER timer;

    // default constructor to prevent core dump
    PARTICLE();

    // user can determine these var
    PARTICLE(float _damping, float _inverseMass, float _gravity
            ,VECTOR _pos, VECTOR _velocity, VECTOR _acceleration );  

    TIMER getTimer();
    VECTOR getForceAccum();
    float getSpeed();
    float getDamping();
    VECTOR getPos();
    VECTOR getAcceleration();
    float getMass();
    VECTOR getVelocity();
    float getElasticity();
    float getInverseMass();

    void setTimer(TIMER& _timer);
    void setForceAccum(VECTOR& _forceAccum);
    void setDamping(float _damping);
    void setPos(VECTOR& _pos);
    void setAcceleration(VECTOR& _acceleration);
    void setPos(VECTOR&& _pos);
    void setMass(float _mass);
    void setInverseMass(float _inverseMass);
    void setVelocity(VECTOR& _velocity);
    void setVelocity(VECTOR&& _v);
    void setElasticity(float _elasticity );

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
    VECTOR getAcceleration(VECTOR force);

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

    /**
     * Use this as a callback function with timer
     * If user want to implement there own method , they just need 
     * to use another class which extend this class and override this
     * method
     * 
    */
    virtual void callbackUpdateFunc(PARTICLE_FORCE_REGISTER* p_force_reg,
                                    float duration);

    virtual void autoUpdatePos(PARTICLE_FORCE_REGISTER* p_force_reg,
                                float duration);

    // if velocity < 1cm/s clr it
    void clrVelocity();

    //is the particle moving or not
    bool ismoving();
};

#endif
