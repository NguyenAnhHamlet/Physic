#ifndef __FORCE__VIS__
#define __FORCE__VIS__

#include<ctime>

class PFGEN;
class GFGEN;
class PARTICLE_DRAG;
class PARTICLE;

class FORCE_VISITOR //: public UPDATE_FORCE_VISITOR_INTERFACE
{
public:
    bool updateForce(GFGEN* gfgen, PARTICLE* particle, float duration);
    bool updateForce(PARTICLE_DRAG* p_drag,PARTICLE* particle, float duration);
};

#endif