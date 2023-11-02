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

void 
GFGEN::visitUpdateForce(FORCE_VISITOR* vis, PARTICLE* particle, float duration)
{
    vis->updateForce(this, particle, duration);
}

static GFGEN* GFGEN::getInstance()
{
    if( !gfgen) gfgen = new GFGEN();
    return gfgen;
}
