#include "common.hpp"
#include <cmath>

float 
convertCM(float pixel)
{
    return (pixel/37.795);
}

unsigned int 
convertPX(float meter)
{
    return (meter * 100 * 37.795);
}

unsigned int hypotenuse(float a, float b)
{
    return sqrt(pow(a,2) + pow(b,2));
}

bool collinearPoints(VECTOR* a, VECTOR* b, VECTOR* c)
{
    if (a->getPos().x == b->getPos().x && b->getPos().x == c->getPos().x) 
        return true; 
    
    float slope12 = (b->getPos().y - a->getPos().y) / (b->getPos().x - a->getPos().x);
    float slope23 = (c->getPos().y - b->getPos().y) / (c->getPos().x - b->getPos().x);
    return abs(slope12 - slope23) < 1e-6;
}