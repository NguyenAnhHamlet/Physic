#include "../gjk.hpp"
#include "../shape.hpp"
#include "../point2D.hpp"
#include "../vector.hpp"


bool addSupport(SHAPE* s1, SHAPE* s2 ,VECTOR* direction) 
{
    VECTOR* newVertex = s1->support(direction) - s2->support( direction * -1);
    vertices.push_back(newVertex);
    return newVertex->scalarProduct(direction) >= 0;
}

void evolveSimplex(SHAPE* s1, SHAPE* s2, std::list<VECTOR*> vertices)
{
    VECTOR* direction;

    switch (vertices.size())
    {
    case 0:
        direction = s1->getCenter() - s2->getCenter();
        vertices.push_back(s1->support(direction) - s2->support(direction * -1));
        break;
    
    case 1 : 
        direction *= -1;
        vertices.push_back(s1->support(direction) - s2->support(direction * -1));
        break;

    case 2 :
        VECTOR* b = vertices[1];
        VECTOR* c = vertices[0];

        // line cb is the line formed by the first two vertices
        VECTOR* cb = b - c;
        // line c0 is the line from the first vertex to the origin
        VECTOR* c0 = c * -1;

        // use the triple-cross-product to calculate a direction perpendicular to line cb
        // in the direction of the origin
        direction = tripleProduct(cb, c0, cb);
        vertices.push(s1->support(direction) - s2->support( direction * -1));
        break;
    
    case 3: 
        // calculate if the simplex contains the origin
        VECTOR* a = vertices[2];
        VECTOR* b = vertices[1];
        VECTOR* c = vertices[0];

        VECTOR* a0 = a * -1; // v2 to the origin
        VECTOR* ab = b - a; // v2 to v1
        VECTOR* ac = c - a; // v2 to v0

        VECTOR* abPerp = tripleProduct(ac, ab, ab);
        VECTOR* acPerp = tripleProduct(ab, ac, ac);

        if(abPerp->scalarProduct(a0) > 0) {
            // the origin is outside line ab
            // get rid of c and add a new support in the direction of abPerp
                vertices.pop_front();
                direction = abPerp;
                vertices.push_back(s1->support(direction) - s2->support( direction * -1));
        }
        else if(acPerp->scalarProduct(a0) > 0) {
            // the origin is outside line ac
            // get rid of b and add a new support in the direction of acPerp
                vertices.erase(b);
                direction = acPerp;
                vertices.push_back(s1->support(direction) - s2->support( direction * -1));
        }
        else {
            // the origin is inside both ab and ac,
            // so it must be inside the triangle!
            return EvolveResult.FoundIntersection;
        }

    default:
        break;
    }

    return addSupport(s1, s2, direction) ? EvolveResult.StillEvolving : EvolveResult.NoIntersection;
}