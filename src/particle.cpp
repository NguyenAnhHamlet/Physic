#include "particle.hpp"

PARTICLE::PARTICLE() : damping(0.0), inverseMass(0.0), mass(0.0) {}

PARTICLE::PARTICLE(float _damping, float _inverseMass, float _gravity
            ,VECTOR _pos, VECTOR _velocity, VECTOR _acceleration )
            :damping(_damping), inverseMass(_inverseMass)
            ,pos(_pos), velocity(_velocity), acceleration(_acceleration)
            {}

float 
PARTICLE::getMass()
{
    return this->mass;
}

void 
PARTICLE::init()
{
    speed = velocity.magnitude();
}

void 
PARTICLE::posUpdate(VECTOR velocity, float duration)
{
    assert(duration > 0.0);

    pos = pos + velocity * duration;
}

void 
PARTICLE::posUpdate(VECTOR velocity, VECTOR acceleration, float duration )
{
    assert(duration > 0.0);

    // Calculate velocity from force and apply it
    this->velocity = this->velocity + getVelocity(forceAccum, duration);

    /**
     * using integration to calculate the next position of
     * this particle in given duration
     * p2 = p1 + p.'t + p''.t^2/2
    */
    pos = pos + velocity * duration;
    pos = pos + acceleration * duration*duration/2;
}

void 
PARTICLE::addForce(const VECTOR& force)
{
    this->forceAccum = this->forceAccum + force;
}

VECTOR
PARTICLE::getAcceleration(VECTOR force)
{
    return force / (float) mass;
}

void
PARTICLE::setGravity(GFGEN* _gravityForce)
{
    this->gravityForce = *(_gravityForce);
}

void 
PARTICLE::setDrag(PARTICLE_DRAG* _dragForce)
{
    this->dragForce = *(_dragForce);
}

void 
PARTICLE::clearForce()
{
    this->forceAccum.clear();
}

VECTOR PARTICLE::getVelocity(const VECTOR& force, float duration)
{
    VECTOR _acceleration = getAcceleration(force);
    _acceleration = _acceleration * duration;
    return this->velocity + _acceleration;
}