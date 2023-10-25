#include "vector.hpp"
#include "particle.hpp"
#include "particleDrag.hpp"
#include "particleForceRegister.hpp"
#include "particleRegister.hpp"
#include <list>
#include "pfgen.hpp"
#include "forceVisitor.hpp"
#include <ctime>

int main()
{
    clock_t t = (float) 0.001;
    std::cout<<t;
    PARTICLE* particle = new PARTICLE();
    VECTOR vector(1000, 1000, 0);
    TIMER timer;

    particle->setVelocity(vector);
    PARTICLE_DRAG* dragForce = new PARTICLE_DRAG();
    dragForce->setDrag(2, 2);
    particle->setMass((float)1.2);
    particle->setTimer(timer);

    particle->init();

    PARTICLE_FORCE_REGISTER* forceRegister = new PARTICLE_FORCE_REGISTER();
    // PARTICLE_REGISTER* pregister = new PARTICLE_REGISTER(forceRegister);

    std::list<PFGEN*> list{ static_cast<PFGEN*>(dragForce)};
    forceRegister->add(particle,list);

    FORCE_VISITOR* vis = new FORCE_VISITOR();

    particle->autoUpdatePos(forceRegister, vis, (float)0.02);
    particle->CountDown ? (std::cout<<"NULL") : (std::cout<<"NOT NULL");
    particle->CountDown->join();
    
    // pregister->getPfregister()->add(particle, list);
    // pregister->initAll();
    // pregister->runAll();

    return 0;
}

