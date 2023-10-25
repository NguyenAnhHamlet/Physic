#include "forceVisitor.hpp"
#include "gfgen.hpp"
#include "particleDrag.hpp"

bool 
FORCE_VISITOR::updateForce(GFGEN* gfgen, PARTICLE* particle, float duration)
{
    if(!gfgen) return false;
    gfgen->updateForce(particle, duration);
    return true;
}

bool
FORCE_VISITOR::updateForce(PARTICLE_DRAG* p_drag, PARTICLE* particle, float duration)
{
    if(!p_drag) return false;
    p_drag->updateForce(particle,duration);
    return true;
}

