#ifndef __PFR__
#define __PFR__

#include "force/pfgen.hpp"
#include<list>
#include<map>

class PARTICLE;

typedef std::map<SHAPE*,std::list<PFGEN*>> Registry;

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
    PARTICLE_FORCE_REGISTER();
    Registry* getRegis();
    /**
     *  Add new particle and a list of force being applied 
     *  upon it
    */
    void add(SHAPE* shape, std::list<PFGEN*> listForceGen);

    /**
     *  Remove particle from the regis
     * 
     *  Both the particle and force being applied 
     *  upon it will be removed completely from 
     *  regis list . 
    */
    void remove(SHAPE* shape);

    /**
     *  Remove all regis 
    */
    void clear();
    
    /**
     *  Call all force generator to update force 
     *  of each particular particle 
    */
    void updateForce(SHAPE* shape,float duration);
};

#endif
