#include "vector.hpp"
#include "particle.hpp"
#include "particleDrag.hpp"

int main()
{
    PARTICLE* particle = new PARTICLE();
    VECTOR vector(100, 100, 0);
    TIMER timer;

    particle->setVelocity(vector);
    particle->dragForce.setDrag(2, 2);
    particle->setMass((float)1.2);
    particle->setTimer(timer);

    particle->timer.setCallback(&PARTICLE::callbackFunc);

    particle->autoUpdatePos();

}

