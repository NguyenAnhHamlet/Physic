#include "gjk/gjk.hpp"
#include "render/shape.hpp"
#include "bvh/point2D.hpp"
#include "base/Vector3D.hpp"
#include<vector>


bool addSupport(SHAPE* s1, SHAPE* s2 ,Vector3D& direction, 
                std::vector<Vector3D>& vertices) 
{
    Vector3D newVertex = s1->support(direction) 
                         - s2->support( direction * -1);
    vertices.push_back(newVertex);
    return newVertex.scalarProduct(direction) >= 0;
}

EvolveResult evolveSimplex(SHAPE* s1, SHAPE* s2, 
                           std::vector<Vector3D>& vertices, 
                           Vector3D& direction)
{
    switch (vertices.size())
    {
        case 0:
        {
            Vector3D c1 = *(s1->getCenter());
            Vector3D c2 = *(s2->getCenter());
            direction = c1 - c2;
            break;
        }
        
        case 1: 
        {
            direction = direction * -1;
            break;
        }

        case 2:
        {
            Vector3D b = vertices[1];
            Vector3D c = vertices[0];

            // line cb is the line formed by the first two vertices
            Vector3D cb = b - c;
            // line c0 is the line from the first vertex to the origin
            Vector3D c0 = c * -1;

            // use the triple-cross-product to calculate a direction 
            // perpendicular to line cb
            // in the direction of the origin
            direction = tripleProduct(cb, c0, cb);
            break;
        }
        
        case 3: 
        {
            // calculate if the simplex contains the origin
            Vector3D a = vertices[2];
            Vector3D b = vertices[1];
            Vector3D c = vertices[0];

            Vector3D a0 = a * -1; // v2 to the origin
            Vector3D ab = b - a; // v2 to v1
            Vector3D ac = c - a; // v2 to v0

            Vector3D abPerp = tripleProduct(ac, ab, ab);
            Vector3D acPerp = tripleProduct(ab, ac, ac);

            if(abPerp.scalarProduct(a0) > 0) {
                // the origin is outside line ab
                // get rid of c and add a new support 
                // in the direction of abPerp
                    vertices.erase(vertices.begin());
                    direction = abPerp;
            }
            else if(acPerp.scalarProduct(a0) > 0) {
                // the origin is outside line ac
                // get rid of b and add a new support in 
                // the direction of acPerp
                    vertices.erase(vertices.begin() + 1);
                    direction = acPerp;
            }
            else {
                // the origin is inside both ab and ac,
                // so it must be inside the triangle!
                return EvolveResult::FoundIntersection;
            }
        }

        default:
        {
            return EvolveResult::Error;
        }
    }

    return addSupport(s1, s2, direction, vertices) ? 
           EvolveResult::StillEvolving : 
           EvolveResult::NoIntersection;
}