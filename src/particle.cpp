#include "particle.hpp"
#include "particleForceRegister.hpp"
#include "timer.hpp"

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
    std::cout<<duration<<'\n';
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
PARTICLE::autoUpdatePos(PARTICLE_FORCE_REGISTER* p_force_reg, FORCE_VISITOR* vis, 
                        float duration)
{
    // std::cout<<duration<<'\n';
    if(!(this->CountDown))
    {
        this->CountDown =  timer.runCountDown(this, p_force_reg, vis, duration);
        this->CountDown ? (std::cout<<"NOT NULL") : (std::cout<<"NULL");
    }
}

void 
PARTICLE::callbackUpdateFunc(PARTICLE_FORCE_REGISTER* p_force_reg, 
                            FORCE_VISITOR* vis, float duration)
{
    p_force_reg->updateForce(vis, this, duration);
    posUpdate(this->velocity,this->acceleration, duration);
    this->clearForce();
    std::cout << this->getPos().x << "," << this->getPos().y << "," << this->getVelocity().x << '\n';
}