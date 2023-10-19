#include "particleDrag.hpp"
#include"particle.hpp"
#include"pfgen.hpp"
#include"vector.hpp"

PARTICLE_DRAG::PARTICLE_DRAG(float _k1, float _k2) 
                : k1(_k1), k2(_k2) 
                {}
                
void PARTICLE_DRAG::updateForce(PARTICLE* particle, float duration)
{
    float dragCoeff = particle->getVelocity().magnitude();
    dragCoeff = k1* dragCoeff + k2* dragCoeff* dragCoeff;

    VECTOR force = particle->getVelocity().normalize();
    force = force * (- 1 * dragCoeff);
    
    particle->addForce(force);
}

PARTICLE_DRAG::PARTICLE_DRAG()
{
}

void PARTICLE_DRAG::setDrag(float _k1, float _k2 )
{
    this->k1 = _k1;
    this->k2 = _k2;
}
