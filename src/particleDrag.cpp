#include "particleDrag.hpp"
#include"particle.hpp"
#include"pfgen.hpp"
#include"vector.hpp"

PARTICLE_DRAG::PARTICLE_DRAG(float _k1, float _k2) 
                : k1(_k1), k2(_k2) 
                {}
                
void PARTICLE_DRAG::updateForce(PARTICLE* particle, float duration)
{
    VECTOR direction = particle->velocity.direction();

    VECTOR force = direction * k1 
                    + direction* direction * k2; 
    force = force * direction * -1;
    
    particle->addForce(force);
}

PARTICLE_DRAG::PARTICLE_DRAG()
{
}
