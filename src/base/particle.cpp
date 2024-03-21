#include "particle.hpp"
#include "particleForceRegister.hpp"
#include "timer.hpp"
#include "common.hpp"
#include <utility> 
#include "shape.hpp"

PARTICLE::PARTICLE() : damping(0.0), inverseMass(0.0), mass(0.0) 
{
    init();
}

PARTICLE::PARTICLE(float _damping, float _inverseMass, float _gravity
            ,VECTOR _pos, VECTOR _velocity, VECTOR _acceleration )
            :damping(_damping), inverseMass(_inverseMass)
            ,pos(_pos), velocity(_velocity), acceleration(_acceleration)
{
    init();
}

float 
PARTICLE::getMass()
{
    return this->mass;
}

void 
PARTICLE::init()
{
    speed = velocity.magnitude();
    this->timer.setCallback(&PARTICLE::callbackUpdateFunc);
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
    VECTOR _velocity = getVelocity(forceAccum, duration);
    this->velocity = this->velocity + _velocity;

    /**
     * using integration to calculate the next position of
     * this particle in given duration
     * p2 = p1 + p.'t + p''.t^2/2
    */
    pos = pos + this->velocity * duration;
    pos = pos + acceleration * duration*duration/2;

    std::cout << "VELOCITY : " << this->velocity.y <<'\n';

    clearForce();
    
}

void 
PARTICLE::addForce(const VECTOR& force)
{
    forceAccum = forceAccum + force;

    std::cout << "FORCE:" << forceAccum.y << '\n';
}

VECTOR
PARTICLE::getAcceleration(VECTOR force)
{
    return force / (float) mass;
}
TIMER 
PARTICLE::getTimer()
{
    return this->timer;
}

VECTOR 
PARTICLE::getForceAccum()
{
    return forceAccum;
}

float 
PARTICLE::getSpeed()
{
    return speed;
}

float 
PARTICLE::getDamping()
{
    return damping;
}

VECTOR 
PARTICLE::getPos()
{
    return pos;
}

VECTOR 
PARTICLE::getAcceleration()
{
    return acceleration;
}

void 
PARTICLE::setTimer(TIMER& _timer)
{
    timer = _timer;
}

void 
PARTICLE::setForceAccum(VECTOR& _forceAccum)
{
    forceAccum = _forceAccum;
}

void 
PARTICLE::setDamping(float _damping)
{
    damping = _damping;
}

void 
PARTICLE::setPos(VECTOR& _pos)
{
    pos = _pos;
}

void 
PARTICLE::setPos(VECTOR&& _pos)
{
    pos = std::move(_pos);
}


void 
PARTICLE::setAcceleration(VECTOR& _acceleration)
{
    acceleration = _acceleration;
}

void
PARTICLE::setMass(float _mass)
{
    mass = _mass;
}

void 
PARTICLE::clearForce()
{
    forceAccum.clear();
}

VECTOR 
PARTICLE::getVelocity(const VECTOR& force, float duration)
{
    VECTOR _acceleration = getAcceleration(force);
    _acceleration = _acceleration * duration;
    return _acceleration;
}

VECTOR 
PARTICLE::getVelocity()
{
    return this->velocity; 
}

void 
PARTICLE::setVelocity(VECTOR& _velocity)
{
    this->velocity = _velocity;
}

void 
PARTICLE::autoUpdatePos(PARTICLE_FORCE_REGISTER* p_force_reg, 
                        float duration)
{
    if(!(this->CountDown))
    {
        this->CountDown =  timer.runCountDown(this, p_force_reg, duration);
    }
}

void 
PARTICLE::callbackUpdateFunc(PARTICLE_FORCE_REGISTER* p_force_reg, 
                            float duration)
{
    p_force_reg->updateForce(dynamic_cast<SHAPE*>(this), duration);
    posUpdate(velocity, acceleration, duration);
    this->clearForce();
}

void 
PARTICLE::clrVelocity()
{
    if(convertCM(this->velocity.x) < 1) this->velocity.x = 0;
    if(convertCM(this->velocity.y) < 1) this->velocity.y = 0;
    if(convertCM(this->velocity.z) < 1) this->velocity.z = 0;
}

float
PARTICLE::getElasticity()
{
    return elasticity;
}

void 
PARTICLE::setElasticity(float _elasticity)
{
    assert(_elasticity > 0.0);
    assert(_elasticity <= 1.0);
    elasticity = _elasticity;
}

float 
PARTICLE::getInverseMass()
{
    return inverseMass;
}

void 
PARTICLE::setInverseMass(float _inverseMass)
{
    inverseMass = _inverseMass;
}

bool 
PARTICLE::ismoving()
{
    if(!velocity.x & !velocity.y & !velocity.z)
        return false;
    return true;
}

void 
PARTICLE::setVelocity(VECTOR&& _v)
{
    velocity = std::move(_v);
}