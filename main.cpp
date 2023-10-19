#include "vector.hpp"
#include "particle.hpp"
#include "particleDrag.hpp"

int main()
{
    VECTOR* vector = new VECTOR(100,100,0);
    PARTICLE* particle = new PARTICLE();

    particle->setVelocity(*vector);
    particle->dragForce.setDrag(2, 2);
    particle->setMass((float)1.2);

    for(int i=100; i>=0; i--)
    {
        particle->dragForce.updateForce(particle, (float)0.001);
        //std::cout<<particle->forceAccum.x<<particle->forceAccum.y<<particle->forceAccum.z<<'\n';
        particle->posUpdate(particle->getVelocity(),
                            particle->getAcceleration(),(float)0.001);

        particle->clearForce();

        std::cout << particle->getPos().x << "," << particle->getPos().y << "," << particle->getVelocity().z << '\n';

    }
}

