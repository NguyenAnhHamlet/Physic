#include "vector.hpp"

int main()
{
    VECTOR* vector = new VECTOR(1,2,0);
    PARTICLE* particle = new PARTICLE();

    particle->velocity = *vector;

    for(int i=15; i>=0; i--)
    {
        particle->dragForce->updateForce(particle,0.001);
        particle->posUpdate(particle->velocity,
                            particle->acceleration,0.001);

        std::cout<<particle->velocity.x <<" "<<particle->velocity.y
                 <<particle->velocity.z<<'\n';

    }
}

