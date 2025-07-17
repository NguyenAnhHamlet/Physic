#ifndef __BOUNDS__
#define __BOUNDS__

// Bounds2D is used for the purpose of creating a bound around a 
// set of primitive for splitting purpose.

// Some components needed for SAH algorithm and DFS traversal including 
// pMin, pMax :        help to determine the space which this bound occupies
// centroid :          help to sort a vector of bounds_vector
// shape :             this is optional, only leaf level hold a shape, for simplify 
//                     the updating position of Bounds2D 
// numOfPrimitives :   for calculating cost in SAH 
// numRetry :          the number of times SAH algorithm would try to split

#include<iostream>
#include <utility>
#include "bvh/point2D.hpp"
#include <vector>
#include "common/common.hpp"
#include <cfloat>
#include "render/shape.hpp"

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
    SHAPE* shape = NULL;
    unsigned int numOfPrimitives;
    unsigned int numRetry;
    
public:
    int num = 0;
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

    Bounds2D(SHAPE* s, float _w , float _h)
            : shape(s), w(_w), h(_h)
            {
                update();
            }

    ~Bounds2D()
    {
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

    // get pair with first is pMin and 2nd is pMax
    std::pair<point2D,point2D> getPoints() const;

    // get function
    unsigned int getNumPrimitives() const;
    point2D getpMin() const { return pMin; }
    point2D getpMax() const { return pMax ;}
    point2D getCentroid() const { //printf("value: %d\n", num); 
                                  //printf("centroidx: %d\n", centroid.x);
                                  return centroid ;}
    unsigned int getNumRetry() const {return numRetry ;}
    SHAPE* getShape() const { return shape ;}
    float getW() const {return w ;}
    float getH() const {return h ;}

    // set function 
    void setNumPrimitives(unsigned int n);
    void setpMin(const point2D& p) {pMin = p ;}
    void setpMax(const point2D& p) {pMax = p ;}
    void setCentroid(const point2D& c) {centroid = c ;}
    void setNumRetry(unsigned int n) {numRetry = n ;}
    void setShape(SHAPE* s) { shape = s; }
    void setHeight(const float height) { h = height; }
    void setWidth(const float width) {w = width; }

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
        if(!shape)
        {
            return;
        } 
        pMin = point2D(shape->getCenter()->x - w, shape->getCenter()->y -h );
    }

    void setpMax() 
    {
        if(!shape) return;
        pMax = point2D(shape->getCenter()->x + w, shape->getCenter()->y + h);
    }

    void setCentroid() 
    {  
        if(!shape)
        {
            centroid = point2D(pMin.x + (pMax.x - pMin.x)/2, pMin.y + (pMax.y - pMin.y )/2);
        }
        else 
        {
            centroid = point2D(shape->getCenter()->x, shape->getCenter()->y );
        }
    }

    void update();
};

typedef std::vector<Bounds2D> bounds_vector;

// check if 2 Bounds overlap each other or not
bool doOverlap(const Bounds2D& b1, const Bounds2D& b2);

// check if bound b overlap Axis with val or not
bool doOverlap(const Bounds2D& b, float val, axis Axis);

// return the bound that bounds both of b1, b2
Bounds2D getTotalBounds(const Bounds2D& b1, const Bounds2D& b2);

// return the total bound of b1, b2
Bounds2D* getTotalBounds(Bounds2D* b1, Bounds2D* b2);

/**
 *  split the bound with axis
 *  if user wish to get the bound of x axis then pass value of x in side as argument,
 *  the return value will be pair with pair.first is left and pair.second is right
 *  if user wish to get the bound of y axis then pass value of y in side as argument
 *  the return value will be pair with pair.first is top and pair.second is bottom
*/
std::pair<Bounds2D*, Bounds2D*> splitAxis(const Bounds2D& b, float xAxis = -1, float yAxis = -1);
std::pair<Bounds2D*, Bounds2D*> splitAxis(const Bounds2D& b, std::pair<float, float> p_split, axis _axis );

// create a bound around the shape
// using overloadding
Bounds2D createBound(SHAPE* shape);
Bounds2D createBound(CIRCLE* cir);
Bounds2D createBound(RECTANGLE* rect);

// get bound of each shape and return the list of all of them 
bounds_vector getBoundEach(set_shape_holder* _set_shape_holder);

// get bound of all bound inside bounds_vector
Bounds2D getBoundAll(const bounds_vector& b_vec);

// return true if the coordination is in Bounds2D
bool isInBounds(const Bounds2D* b, std::pair<float,float> coor);

// return true if b1 lies within b2 or vice versa
bool isInBounds(const Bounds2D* b1, const Bounds2D* b2 );

#endif