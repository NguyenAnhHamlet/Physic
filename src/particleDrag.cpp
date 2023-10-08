#include "particleDrag.hpp"

void PARTICLE_DRAG::updateForce(PARTICLE* particle, float duration)
{
    VECTOR direction = particle->velocity.direction();

    VECTOR force = direction.multiply(k1) 
                    + direction.multiply(direction.multiply(k2)); 
    force.multiply(direction.multiply(-1));
    
    particle->addForce(force);
}