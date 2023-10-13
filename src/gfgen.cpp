#include "gfgen.hpp"

GFGEN::GFGEN() {}

void
GFGEN::updateForce(PARTICLE* particle, float duration)
{
    particle->addForce(gravity.multiply(particle->getMass()));
}

