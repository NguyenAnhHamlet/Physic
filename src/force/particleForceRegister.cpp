#include "force/particleForceRegister.hpp"
#include "base/particle.hpp"

PARTICLE_FORCE_REGISTER::PARTICLE_FORCE_REGISTER()
{
    
}

void 
PARTICLE_FORCE_REGISTER::add(SHAPE* shape, std::list<PFGEN*> listForceGen)
{
    this->regis.insert({shape,listForceGen});
}

void 
PARTICLE_FORCE_REGISTER::add(SHAPE* shape, PFGEN* force)
{
    std::list<PFGEN*> listForceGen = {force};
    this->regis.insert({shape, listForceGen});
}

void 
PARTICLE_FORCE_REGISTER::remove(SHAPE* shape)
{
    this->regis.erase(shape);
}

void 
PARTICLE_FORCE_REGISTER::clear()
{
    this->regis.clear();
}

void 
PARTICLE_FORCE_REGISTER::updateForce(SHAPE* shape,float duration)
{  
    for(auto force : regis[shape] )
    {
        force->updateForce(shape,duration);
    } 
}

Registry* 
PARTICLE_FORCE_REGISTER::getRegis()
{
    return &(this->regis);
}

void 
PARTICLE_FORCE_REGISTER::updateForceAll(float duration)
{
    assert(duration > 0);

    for(auto regis_pair : regis)
    {
        updateForce(regis_pair.first, duration);
    }
}