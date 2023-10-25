#ifndef __FORCE__VIS__
#define __FORCE__VIS__

#include<ctime>

class PFGEN;
class GFGEN;
class PARTICLE_DRAG;
class PARTICLE;

class FORCE_VISITOR 
{
public:
    void updateForce(GFGEN* gfgen, PARTICLE* particle, float duration);
    void updateForce(PARTICLE_DRAG* p_drag,PARTICLE* particle, float duration);
};

#endif