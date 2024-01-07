#include "gfgen.hpp"
#include "particle.hpp"
#include "pfgen.hpp"
#include "vector.hpp"

GFGEN::GFGEN() {}

void
GFGEN::updateForce(PARTICLE* particle, float duration)
{
    particle->addForce(gravity * particle->getMass());
}