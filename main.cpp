#include "vector.hpp"
#include "particle.hpp"
#include "particleDrag.hpp"

int main()
{
    VECTOR* vector = new VECTOR(100,100,0);
    PARTICLE* particle = new PARTICLE();

    particle->velocity = *vector;
    particle->dragForce.setDrag(1.5,1.5);
    particle->mass = 1.2;

    for(int i=100; i>=0; i--)
    {
        particle->dragForce.updateForce(particle, (float)0.001);
        std::cout<<particle->forceAccum.x<<particle->forceAccum.y<<particle->forceAccum.z<<'\n';
        particle->posUpdate(particle->velocity,
                            particle->acceleration,(float)0.001);

        particle->clearForce();

        std::cout << particle->pos.x << "," << particle->pos.y << "," << particle->velocity.z << '\n';

    }
}

