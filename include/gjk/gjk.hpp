#ifndef __GJK__ 
#define __GJK__

#include "bvh/point2D.hpp"
#include "render/shape.hpp"
#include<list>

enum EvolveResult 
{
    NoIntersection,
    FoundIntersection,
    StillEvolving,
    Error
};

bool addSupport(SHAPE* s1, SHAPE* s2 ,Vector3D& direction, std::vector<Vector3D>& vertices);
EvolveResult evolveSimplex(SHAPE* s1, SHAPE* s2, std::vector<Vector3D>& vertice, Vector3D& directions);

#endif