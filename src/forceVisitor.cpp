#include "forceVisitor.hpp"
#include "gfgen.hpp"
#include "particleDrag.hpp"

void 
FORCE_VISITOR::updateForce(PFGEN* pfgen, PARTICLE* particle, float duration)
{
    if(updateForce(static_cast<GFGEN*>(pfgen),particle, duration)) return;
    if(updateForce(static_cast<PARTICLE_DRAG*>(pfgen), particle, duration)) return;
}

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

