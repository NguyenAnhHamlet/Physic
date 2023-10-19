#include "vector.hpp"
#include "particle.hpp"
#include "particleDrag.hpp"

int main()
{
    VECTOR* vector = new VECTOR(100,100,0);
    PARTICLE* particle = new PARTICLE();
    TIMER* timer = new TIMER();

    particle->setVelocity(*vector);
    particle->dragForce.setDrag(2, 2);
    particle->setMass((float)1.2);
    particle->setTimer(*timer);

    timer->setCallback(&PARTICLE::autoUpdatePos);

    timer->runCountDown(particle,(clock_t)0.001);
}

