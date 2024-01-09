#include <iostream>
#include<utility>
#include "bounds.hpp"
#include "shape.hpp"
#include "point2D.hpp"

bool doOverlap(const Bounds2D& b1, const Bounds2D& b2)
{

    // If one rectangle is on left side of other
    if (b1.getPoints().first.x > b2.getPoints().second.x || 
        b2.getPoints().first.x > b1.getPoints().second.x)

        return false;
 
    // If one rectangle is above other
    if (b1.getPoints().second.y > b2.getPoints().first.y ||
        b2.getPoints().second.y > b1.getPoints().first.y)
        return false;

    return true;
}

std::pair<point2D,point2D> Bounds2D::getPoints() const
{
    return {pMin, pMax};
}

void Bounds2D::setNumPrimitives(unsigned int n)
{
    numOfPrimitives = n;
}

Bounds2D getTotalBounds(const Bounds2D& b1, const Bounds2D& b2) {
    point2D _pMin(  std::min(b1.getpMin().x, b2.getpMin().x), 
                    std::min(b1.getpMin().y, b2.getpMin().y));

    point2D _pMax(  std::max(b1.getpMax().x, b2.getpMax().x), 
                    std::max(b1.getpMax().y, b2.getpMax().y));

    point2D centroid(_pMin.x + _pMax.x /2, _pMin.y + _pMax.y / 2);

    Bounds2D res(_pMin, _pMax, centroid);
    return res;
}

std::pair<Bounds2D*, Bounds2D*> splitAxis(const Bounds2D& b, float xAxis , float yAxis )
{
    std::pair<Bounds2D*, Bounds2D*> res;
    point2D pMin, pMax;

    if(xAxis != -1)
    {
        res.first = new Bounds2D(   point2D(b.getPoints().first.x,b.getPoints().first.y), 
                                    point2D(std::max(b.getPoints().second.x, xAxis), b.getPoints().second.y));

        res.second = new Bounds2D(  point2D(std::max(b.getPoints().first.x, xAxis),b.getPoints().first.y), 
                                    point2D(b.getPoints().second.x, b.getPoints().second.y));

    }

    if(yAxis != -1)
    {
        res.first = new Bounds2D(   point2D(b.getPoints().first.x,b.getPoints().first.y), 
                                    point2D(b.getPoints().second.x, std::max(b.getPoints().second.y, yAxis)));

        res.second = new Bounds2D(  point2D(b.getPoints().first.x,std::max(b.getPoints().first.y,yAxis)), 
                                    point2D(b.getPoints().second.x, b.getPoints().second.y));
    }


    res.first->setCentroid();
    res.second->setCentroid();

    return res;
}

unsigned int Bounds2D::getNumPrimitives() const 
{
    return numOfPrimitives;
}

Bounds2D createBound(SHAPE* shape)
{
    if(static_cast<CIRCLE*>(shape))
    {
        return createBound(static_cast<CIRCLE*>(shape));
    }
    else
    {
        return createBound(static_cast<RECTANGLE*>(shape));
    }
}

Bounds2D createBound(CIRCLE* cir)
{
    Bounds2D bound2D(   point2D(cir->getCenter()->x - cir->getR(), cir->getCenter()->y - cir->getR()),
                        point2D(cir->getCenter()->x + cir->getR(), cir->getCenter()->y + cir->getR()));
    
    return bound2D;
}

Bounds2D createBound(RECTANGLE* rect)
{
    Bounds2D bound2D(   point2D(rect->getCenter()->x - rect->getW()/2, rect->getCenter()->y - rect->getH()/2),
                        point2D(rect->getCenter()->x + rect->getW()/2, rect->getCenter()->y + rect->getH()/2));

    return bound2D;
}

bounds_vector getBoundEach(set_shape_holder* _set_shape_holder)
{
    bounds_vector res;

    for(auto it : *_set_shape_holder)
    {
        res.push_back(createBound(it));
    }

    return res;
}

Bounds2D getBoundAll(const bounds_vector& b_vec)
{
    Bounds2D res;

    for(auto it : b_vec)
    {
        res = getTotalBounds(res, it );
    }

    return res;
}

bool doOverlap(const Bounds2D& b, float val, axis Axis)
{
    bool res;

    if(Axis == axis::xAxis)
    {
        if(val > b.getpMin().x && val < b.getpMax().x )
            res = true;
        else 
            res = false;
    }
    else 
    {
        if(val > b.getpMin().y && val < b.getpMax().y )
            res = true;
        else 
            res = false;
    }

    return res;
}

void 
Bounds2D::update()
{
    setpMax();
    setpMax();
    setCentroid();
}

void
Bounds2D::init()
{
    w = pMax.x - centroid.x;
    h = pMin.y - centroid.y;
}

