#include "particle.hpp"
#include "particleForceRegister.hpp"
#include "timer.hpp"
#include "common.hpp"
#include <utility> 

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

    // std::cout << "RUNNING" <<'\n';

    pos = pos + velocity * duration;

    // std::cout << pos.x << " " << pos.y << '\n';
}

void 
PARTICLE::posUpdate(VECTOR velocity, VECTOR acceleration, float duration )
{
    assert(duration > 0.0);
    this->clrVelocity();

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
TIMER 
PARTICLE::getTimer()
{
    return this->timer;
}

VECTOR 
PARTICLE::getForceAccum()
{
    return this->forceAccum;
}

float 
PARTICLE::getSpeed()
{
    return this->speed;
}

float 
PARTICLE::getDamping()
{
    return this->damping;
}

VECTOR 
PARTICLE::getPos()
{
    return this->pos;
}

VECTOR 
PARTICLE::getAcceleration()
{
    return this->acceleration;
}

void 
PARTICLE::setTimer(TIMER& _timer)
{
    this->timer = _timer;
}

void 
PARTICLE::setForceAccum(VECTOR& _forceAccum)
{
    this->forceAccum = _forceAccum;
}

void 
PARTICLE::setDamping(float _damping)
{
    this->damping = _damping;
}

void 
PARTICLE::setPos(VECTOR& _pos)
{
    this->pos = _pos;
}

void 
PARTICLE::setPos(VECTOR&& _pos)
{
    this->pos = std::move(_pos);
}


void 
PARTICLE::setAcceleration(VECTOR& _acceleration)
{
    this->acceleration = _acceleration;
}

void
PARTICLE::setMass(float _mass)
{
    this->mass = _mass;
}

void 
PARTICLE::clearForce()
{
    this->forceAccum.clear();
}

VECTOR 
PARTICLE::getVelocity(const VECTOR& force, float duration)
{
    VECTOR _acceleration = this->getAcceleration(force);
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
    // std::cout<<duration<<'\n';
    if(!(this->CountDown))
    {
        this->CountDown =  timer.runCountDown(this, p_force_reg, duration);
        // this->CountDown ? (std::cout<<"NOT NULL") : (std::cout<<"NULL");
    }
}

void 
PARTICLE::callbackUpdateFunc(PARTICLE_FORCE_REGISTER* p_force_reg, 
                            float duration)
{
    p_force_reg->updateForce(this, duration);
    posUpdate(this->velocity,this->acceleration, duration);
    this->clearForce();
    // std::cout << this->getPos().x << "," << this->getPos().y << "," << this->getVelocity().x << '\n';
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