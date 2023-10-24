#include "gfgen.hpp"
#include "particle.hpp"
#include "pfgen.hpp"
#include "vector.hpp"
#include "forceVisitor.hpp"

GFGEN::GFGEN() {}

void
GFGEN::updateForce(PARTICLE* particle, float duration)
{
    particle->addForce(gravity * particle->getMass());
}

// void 
// GFGEN::updateForce(FORCE_VISITOR* vis, PARTICLE* particle, float duration)
// {
//     vis->updateForce(this);
// }
