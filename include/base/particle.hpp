#ifndef __PARTICLE__
#define __PARTICLE__

#include <iostream>
#include <cmath>
#include <assert.h>

#include "base/Vector3D.hpp"
#include "force/gfgen.hpp"
#include "common/timer.hpp"
#include "force/particleDrag.hpp"
#include "common/common.hpp"

class GFGEN;
class PARTICLE_DRAG;
class Vector3D;
class TIMER;
class PARTICLE_FORCE_REGISTER;

class PARTICLE
{
protected:
    // position of the particle in space
    Vector3D pos;

    // velocity of this particle in space
    Vector3D velocity;

    // acceleration of this particle in space
    Vector3D acceleration;

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
     * Vector3D velocity
     *
     * Default is set to magnitude of velocity Vector3D
    */
    float speed;

    // degree of elasticity
    float elasticity;

public:
    std::thread* CountDown = NULL;
    /**
     * Total force applied uppon this particle
    */
    Vector3D forceAccum;

    TIMER timer;

    // default constructor to prevent core dump
    PARTICLE();

    // user can determine these var
    PARTICLE(float _damping, float _inverseMass, float _gravity
            ,Vector3D _pos, Vector3D _velocity, Vector3D _acceleration );  

    TIMER getTimer();
    Vector3D getForceAccum();
    float getSpeed();
    float getDamping();
    Vector3D getPos();
    Vector3D getAcceleration();
    float getMass();
    Vector3D getVelocity();
    float getElasticity();
    float getInverseMass();

    void setTimer(TIMER& _timer);
    void setForceAccum(Vector3D& _forceAccum);
    void setDamping(float _damping);
    void setPos(Vector3D& _pos);
    void setAcceleration(Vector3D& _acceleration);
    void setPos(Vector3D&& _pos);
    void setMass(float _mass);
    void setInverseMass(float _inverseMass);
    void setVelocity(Vector3D& _velocity);
    void setVelocity(Vector3D&& _v);
    void setElasticity(float _elasticity );

    // use this function after object being created
    void init();

    /**
     *  update the position of this particle in a given time
     *  without acceleration and force
    */
    void posUpdate(Vector3D velocity, float duration);

    //this one update the position of this particle with acceleration and force
    void posUpdate(Vector3D velocity, Vector3D acceleration,
        float duration);

    /**
     * Particle under the effect of gravity has projectile property
     * and to create a realistic effect of a projectile, use
     * the formula:
     * g' = g/s
    */

    //add force onto forceAccum
    void addForce(const Vector3D& force);

    // Get velocity of this particle through force
    Vector3D getAcceleration(Vector3D force);

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
    Vector3D getVelocity(const Vector3D& force, float duration);

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
