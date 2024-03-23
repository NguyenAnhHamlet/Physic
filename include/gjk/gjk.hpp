#ifndef __GJK__ 
#define __GJK__

#include "bvh/point2D.hpp"
#include "render/shape.hpp"
#include<list>

enum EvolveResult 
{
    NoIntersection,
    FoundIntersection,
    StillEvolving
};

EvolveResult evolveSimplex(SHAPE* s1, SHAPE* s2, std::list<Vector3D*> vertices);

#endif