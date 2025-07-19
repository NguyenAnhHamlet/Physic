#ifndef __PFR__
#define __PFR__

#include "force/pfgen.hpp"
#include<list>
#include<map>

class PARTICLE;

/**
 *  Hold particle and its respective applied force
 */
typedef std::map<SHAPE*,std::list<PFGEN*>> Registry;

/**
 *  The design is straight foward, creating an object as a 
 *  placeholder to hold the map<particle, list<force>> which 
 *  enable the updating force easier, since it keeps both 
 *  particle and its applied force. 
 * 
 *  To use this, make sure to create an instance out of this 
 *  then creating a list of applied force for each particle
 *  and add it into the particel force register.
 */

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
    void add(SHAPE* shape, PFGEN* force);
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

    // udpate force for all particle inside regis
    void updateForceAll(float duration);
};

#endif
