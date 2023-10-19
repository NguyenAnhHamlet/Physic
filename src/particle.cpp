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
    //std::cout << this->velocity.x << this->velocity.y << '\n';
    this->velocity = this->velocity + getVelocity(forceAccum, duration);
    //std::cout << this->velocity.x << this->velocity.y << '\n';
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
TIMER PARTICLE::getTimer()
{
    return this->timer;
}

PARTICLE_DRAG PARTICLE::getDragForce()
{
    return this->dragForce;
}

GFGEN PARTICLE::getGravityForce()
{
    return this->gravityForce;
}

VECTOR PARTICLE::getForceAccum()
{
    return this->forceAccum;
}

float PARTICLE::getSpeed()
{
    return this->speed;
}

float PARTICLE::getDamping()
{
    return this->damping;
}

VECTOR PARTICLE::getPos()
{
    return this->pos;
}

VECTOR PARTICLE::getAcceleration()
{
    return this->acceleration;
}

void PARTICLE::setTimer(TIMER& _timer)
{
    this->timer = _timer;
}

void PARTICLE::setDragFroce(PARTICLE_DRAG& _dragForce) 
{
    this->dragForce = _dragForce;
}

void PARTICLE::getGravityForce(GFGEN& _gfgen)
{
    this->gravityForce = _gfgen;
}

void PARTICLE::setForceAccum(VECTOR& _forceAccum)
{
    this->forceAccum = _forceAccum;
}

void PARTICLE::setDamping(float _damping)
{
    this->damping = _damping;
}

void PARTICLE::setPos(VECTOR& _pos)
{
    this->pos = _pos;
}

void PARTICLE::setAcceleration(VECTOR& _acceleration)
{
    this->acceleration = _acceleration;
}

void
PARTICLE::setMass(float _mass)
{
    this->mass = _mass;
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

VECTOR 
PARTICLE::getVelocity(const VECTOR& force, float duration)
{
    VECTOR _acceleration = getAcceleration(force);
    _acceleration = _acceleration * duration;
    return _acceleration;
}

VECTOR PARTICLE::getVelocity()
{
    return this->velocity; 
}

void PARTICLE::setVelocity(VECTOR& _velocity)
{
    this->velocity = _velocity;
}

