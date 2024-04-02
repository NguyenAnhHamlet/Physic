#ifndef __GJK__ 
#define __GJK__

#include "bvh/point2D.hpp"
#include "render/shape.hpp"
#include<list>

enum EvolveResult 
{
    NoIntersection,
    FoundIntersection,
<<<<<<< HEAD
    StillEvolving,
    Error
};

bool addSupport(SHAPE* s1, SHAPE* s2 ,Vector3D& direction, std::vector<Vector3D> vertices);
EvolveResult evolveSimplex(SHAPE* s1, SHAPE* s2, std::vector<Vector3D> vertice, Vector3D& directions);
=======
    StillEvolving
};

EvolveResult evolveSimplex(SHAPE* s1, SHAPE* s2, std::list<Vector3D*> vertices);
>>>>>>> f643c6cccabf372d6914e417cd8a5ae3c37bb2a5

#endif