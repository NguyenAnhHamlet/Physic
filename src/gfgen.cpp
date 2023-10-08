#include "gfgen.hpp"

void
GFGEN::updateForce(PARTICLE* particle, float duration)
{
    particle->addForce(gravity.multiply(particle.getMass()));
}

