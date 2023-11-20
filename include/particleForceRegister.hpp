#ifndef __PFR__
#define __PFR__

#include "pfgen.hpp"
#include<list>
#include<map>

class FORCE_VISITOR;
class PARTICLE;

typedef std::map<PARTICLE*,std::list<PFGEN*>> Registry;

class 
PARTICLE_FORCE_REGISTER
{
protected:
    /**
     *  Keep all of those particle and force in map 
     *  Easier to keep track of
    */

    Registry regis;

public:
    Registry* getRegis();
    /**
     *  Add new particle and a list of force being applied 
     *  upon it
    */
    void add(PARTICLE* particle, std::list<PFGEN*> listForceGen);

    /**
     *  Remove particle from the regis
     * 
     *  Both the particle and force being applied 
     *  upon it will be removed completely from 
     *  regis list . 
    */
    void remove(PARTICLE* particle);

    /**
     *  Remove all regis 
    */
    void clear();
    
    /**
     *  Call all force generator to update force 
     *  of each particular particle 
    */
    void updateForce(PARTICLE* particle,float duration);
};

#endif
