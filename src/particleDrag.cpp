#include "particleDrag.hpp"

PARTICLE_DRAG::PARTICLE_DRAG(float _k1, float _k2) 
                : k1(_k1), k2(_k2) 
                {}
                
void PARTICLE_DRAG::updateForce(PARTICLE* particle, float duration)
{
    VECTOR direction = particle->velocity.direction();

    VECTOR force = direction.multiply(k1) 
                    + direction.multiply(direction.multiply(k2)); 
    force.multiply(direction.multiply(-1));
    
    particle->addForce(force);
}
