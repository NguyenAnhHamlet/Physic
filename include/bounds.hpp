#ifndef __BOUNDS__
#define __BOUNDS__

#include<iostream>
#include <utility>
#include "point2D.hpp"
#include <vector>

class SHAPE;
class CIRCLE;
class RECTANGLE;
class shape_holder;

class Bounds2D
{
    point2D pMin;
    point2D pMax;
    unsigned int numOfPrimitives;

public:
    Bounds2D() : pMin(point2D pMin(FLT_MAX ,FLT_MAX)), pMax(point2D pMax(FLT_MIN,FLT_MIN)), numOfPrimitives(0) 
    Bounds2D(point2D _pMin, point2D _pMax, unsigned int _numOfPrimitives)
            : pMin(_pMin), pMax(_pMax), numOfPrimitives(_numOfPrimitives) {}

    std::pair<point2D,point2D> getPoints() const;

    /**
     * return the numbers of primitives which this bounds store
    */
    unsigned int getNumPrimitives();
    void setNumPrimitives(unsigned int n);
};

typedef std::vector<Bounds2D*> bounds_vector;

// check if 2 Bounds overlap each other or not
bool doOverlap(const Bounds2D& b1, const Bounds2D& b2);

// return the bound that bounds both of b1, b2
Bounds2D getTotalBounds(const Bounds2D& b1, const Bounds2D& b2);

/**
 *  split the bound with axis
 *  if user wish to get the bound of x axis then pass value of x in side as argument,
 *  the return value will be pair with pair.first is left and pair.second is right
 *  if user wish to get the bound of y axis then pass value of y in side as argument
 *  the return value will be pair with pair.first is top and pair.second is bottom
*/
std::pair<Bounds2D, Bounds2D> splitAxis(const Bounds2D& b, float xAxis = -1, float yAxis = -1);

// create a bound around the shape
Bounds2D createBound(SHAPE* shape);
Bounds2D createBound(CRICLE* cir);
Bounds2D createBound(RECTANGLE* rect);

// get bound of each shape and return the list of all of them 
bounds_vector getBoundEach(set_shape_holder* _set_shape_holder);

// get bound of all bound inside bounds_vector
Bounds2D getBoundAll(const bounds_vector& b_vec);

#endif