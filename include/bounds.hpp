#ifndef __BOUNDS__
#define __BOUNDS__

#include<iostream>
#include <utility>
#include "point2D.hpp"
#include <vector>
#include "common.hpp"
#include <cfloat>
#include "shape.hpp"

class SHAPE;
class CIRCLE;
class RECTANGLE;

class Bounds2D
{
    point2D pMin;
    point2D pMax;
    point2D centroid;
    float w;
    float h;
    SHAPE* shape;
    unsigned int numOfPrimitives;
    unsigned int numRetry;

public:
    Bounds2D() :    pMin(FLT_MAX, FLT_MAX),
                    pMax(FLT_MIN, FLT_MIN),
                    centroid(0,0),
                    numOfPrimitives(0) {}

    Bounds2D(point2D _pMin, point2D _pMax, point2D _centroid, 
            unsigned int _numOfPrimitives, SHAPE* s)
            : pMin(_pMin), pMax(_pMax), centroid(_centroid) ,
             numOfPrimitives(_numOfPrimitives), shape(s) 
             {
                init();
             }

    Bounds2D(point2D _pMin, point2D _pMax, point2D _centroid)
            : pMin(_pMin), pMax(_pMax), centroid(_centroid)
             {
                init();
             }

    Bounds2D(point2D _pMin, point2D _pMax)
            : pMin(_pMin), pMax(_pMax)
             {
                init();
             }

    Bounds2D(SHAPE* s)
            : shape(s)
            {
                update();
                init();
            }

    // copy constructor 
    void operator=(const Bounds2D& b)
    {
        pMin = b.pMin;
        pMax = b.pMax;
        centroid = b.centroid;
        w = b.w;
        h = b.h;
    }

    std::pair<point2D,point2D> getPoints() const;

    // get function
    unsigned int getNumPrimitives() const;
    point2D getpMin() const { return pMin; }
    point2D getpMax() const { return pMax ;}
    point2D getCentroid() const { return centroid ;}
    unsigned int getNumRetry() const {return numRetry ;}
    SHAPE* getShape() const { return shape ;}

    // set function 
    void setNumPrimitives(unsigned int n);
    void setpMin(const point2D& p) {pMin = p ;}
    void setpMax(const point2D& p) {pMax = p ;}
    void setCentroid(const point2D& c) {centroid = c ;}
    void setNumRetry(unsigned int n) {numRetry = n ;}
    void setShape(SHAPE* s) { shape = s; }

    // initialize the needed components
    void init();

    /**
     * Create a completely new bound would be costly, instead
     * just upgrade some components of the bound since it 
     * already store shape, which is the needed attribute to 
     * upgrade the pMax, pMin and centroid in case the bounds 
     * is a leaf
    */
    void setpMin() 
    {
        if(!shape) return;
        pMin = point2D(shape->getCenter()->x - w, shape->getCenter()->y - h);
    }

    void setpMax() 
    {
        if(!shape) return;
        pMin = point2D(shape->getCenter()->x + w, shape->getCenter()->y + h);
    }

    void setCentroid() 
    {  
        if(!shape) return;
        centroid = point2D(shape->getCenter()->x, shape->getCenter()->y );
    }

    void update();
};

typedef std::vector<Bounds2D> bounds_vector;

// check if 2 Bounds overlap each other or not
bool doOverlap(const Bounds2D& b1, const Bounds2D& b2);
bool doOverlap(const Bounds2D& b, float val, axis Axis);

// return the bound that bounds both of b1, b2
Bounds2D getTotalBounds(const Bounds2D& b1, const Bounds2D& b2);

/**
 *  split the bound with axis
 *  if user wish to get the bound of x axis then pass value of x in side as argument,
 *  the return value will be pair with pair.first is left and pair.second is right
 *  if user wish to get the bound of y axis then pass value of y in side as argument
 *  the return value will be pair with pair.first is top and pair.second is bottom
*/
std::pair<Bounds2D*, Bounds2D*> splitAxis(const Bounds2D& b, float xAxis = -1, float yAxis = -1);

// create a bound around the shape
Bounds2D createBound(SHAPE* shape);
Bounds2D createBound(CIRCLE* cir);
Bounds2D createBound(RECTANGLE* rect);

// get bound of each shape and return the list of all of them 
bounds_vector getBoundEach(set_shape_holder* _set_shape_holder);

// get bound of all bound inside bounds_vector
Bounds2D getBoundAll(const bounds_vector& b_vec);

#endif