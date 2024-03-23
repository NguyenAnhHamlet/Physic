#include "base/particle.hpp"
#include "force/particleForceRegister.hpp"
#include "common/timer.hpp"
#include "common/common.hpp"
#include <utility> 
#include "render/shape.hpp"

PARTICLE::PARTICLE() : damping(0.0), inverseMass(0.0), mass(0.0) 
{
    init();
}

PARTICLE::PARTICLE(float _damping, float _inverseMass, float _gravity
            ,Vector3D _pos, Vector3D _velocity, Vector3D _acceleration )
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
PARTICLE::posUpdate(Vector3D velocity, float duration)
{
    assert(duration > 0.0);

    pos = pos + velocity * duration;
}

void 
PARTICLE::posUpdate(Vector3D velocity, Vector3D acceleration, float duration )
{
    assert(duration > 0.0);

    // Calculate velocity from force and apply it
    Vector3D _velocity = getVelocity(forceAccum, duration);
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
PARTICLE::addForce(const Vector3D& force)
{
    forceAccum = forceAccum + force;

    std::cout << "FORCE:" << forceAccum.y << '\n';
}

Vector3D
PARTICLE::getAcceleration(Vector3D force)
{
    return force / (float) mass;
}
TIMER 
PARTICLE::getTimer()
{
    return this->timer;
}

Vector3D 
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

Vector3D 
PARTICLE::getPos()
{
    return pos;
}

Vector3D 
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
PARTICLE::setForceAccum(Vector3D& _forceAccum)
{
    forceAccum = _forceAccum;
}

void 
PARTICLE::setDamping(float _damping)
{
    damping = _damping;
}

void 
PARTICLE::setPos(Vector3D& _pos)
{
    pos = _pos;
}

void 
PARTICLE::setPos(Vector3D&& _pos)
{
    pos = std::move(_pos);
}


void 
PARTICLE::setAcceleration(Vector3D& _acceleration)
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

Vector3D 
PARTICLE::getVelocity(const Vector3D& force, float duration)
{
    Vector3D _acceleration = getAcceleration(force);
    _acceleration = _acceleration * duration;
    return _acceleration;
}

Vector3D 
PARTICLE::getVelocity()
{
    return this->velocity; 
}

void 
PARTICLE::setVelocity(Vector3D& _velocity)
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
PARTICLE::setVelocity(Vector3D&& _v)
{
    velocity = std::move(_v);
}