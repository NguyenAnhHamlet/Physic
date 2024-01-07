#include "common.hpp"
#include <cmath>
#include "vector.hpp"

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
    if (a->x == b->x && b->x == c->x) 
        return true; 
    
    float slope12 = (b->y - a->y) / (b->x - a->x);
    float slope23 = (c->y - b->y) / (c->x - b->x);
    return abs(slope12 - slope23) < 1e-6;
}