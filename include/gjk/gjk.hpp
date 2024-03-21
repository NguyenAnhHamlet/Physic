#ifndef __GJK__ 
#define __GJK__

#include "../point2D.hpp"
#include "../shape.hpp"
#include<list>

enum EvolveResult 
{
    NoIntersection;
    FoundIntersection;
    StillEvolving;
}

void evolveSimplex(SHAPE* s1, SHAPE* s2, std::list<VECTOR*> vertices);

#endif