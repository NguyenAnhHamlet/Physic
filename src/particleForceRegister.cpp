#include "particleForceRegister.hpp"
#include "particle.hpp"

void 
PARTICLE_FORCE_REGISTER::add(PARTICLE* particle, std::list<PFGEN*> listForceGen)
{
    this->regis.insert({particle,listForceGen});
}

void 
PARTICLE_FORCE_REGISTER::remove(PARTICLE* particle)
{
    this->regis.erase(particle);
}

void 
PARTICLE_FORCE_REGISTER::clear()
{
    this->regis.clear();
}

void 
PARTICLE_FORCE_REGISTER::updateForce(PARTICLE* particle,float duration)
{  
    for(auto force : this->regis[particle] )
    {
        force->updateForce(particle,duration);
    } 
}

Registry* 
PARTICLE_FORCE_REGISTER::getRegis()
{
    return &(this->regis);
}