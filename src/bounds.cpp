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

Bounds2D getTotalBounds(const Bounds2D& b1, const Bounds2D& b2)
{
    point2D _pMin = point2D(std::min(b1.getPoints().first.x, b2.getPoints().first.x), 
                            std::min(b1.getPoints().first.y, b2.getPoints().first.y));
    point2D _pMax = point2D(std::max(b1.getPoints().second.x, b2.getPoints().second.x),
                            std::max(b1.getPoints().second.x, b2.getPoints().second.x));

    return Bounds2D res(_pMin, _pMax, b1.getNumPrimitives() + b2.getNumPrimitives());
}

std::pair<Bounds2D, Bounds2D> splitAxis(const Bounds2D& b, float xAxis = -1, float yAxis = -1)
{
    std::pair<Bounds2D, Bounds2D> res;

    if(xAxis != -1)
    {
        res.first = Bounds2D bounds2D(  point2D pMin(b1.getPoints().first.x,b1.getPoints().first.y), 
                                        point2D pMax(std::max(b1.getPoints().second.x, xAsix), b1.getPoints().second.y));

        res.second = Bounds2D bounds2D( point2D pMin(std::max(b1.getPoints().first.x, xAsix),b1.getPoints().first.y), 
                                        point2D pMax(b1.getPoints().second.x, b1.getPoints().second.y));
    }

    if(yAxis != -1)
    {
        res.first = Bounds2D bounds2D(  point2D pMin(b1.getPoints().first.x,b1.getPoints().first.y), 
                                        point2D pMax(b1.getPoints().second.x, std::max(b1.getPoints().second.y, yAxis)));

        res.second = Bounds2D bounds2D( point2D pMin(b1.getPoints().first.x,std::max(b1.getPoints().first.y,yAxis)), 
                                        point2D pMax(b1.getPoints().second.x, b1.getPoints().second.y));
    }

    // have to count how many primitives are there in each side

    return res;
}

unsigned int Bounds2D::getNumPrimitives()
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

Bounds2D createBound(CRICLE* cir)
{
    return Bounds2D bound2D(point2D pMin(cir->getCenter().x - cir->getR(), cir->getCenter().y - cir->getR())
                            point2D pMax(cir->getCenter().x + cir->getR(), cir->getCenter().y + cir->getR()));
}

Bounds2D createBound(RECTANGLE* rect)
{
    return Bounds2D bound2D(point2D pMin(rect->getCenter().x - rect->getW()/2, rect->getCenter().y - rect->getH()/2)
                            point2D pMax(rect->getCenter().x + rect->getW()/2, rect->getCenter().y + rect->getH()/2));
}

bounds_vector getBoundEach(set_shape_holder* _set_shape_holder)
{
    bounds_vector res;

    for(auto it : set_shape_holder)
    {
        res.push_back(createBound(it));
    }

    return res;
}

Bounds2D getBoundAll(const bounds_vector& b_vec)
{
    Bounds2D res();

    for(auto it : b_vec)
    {
        res = getTotalBounds(bound2D,*it );
    }

    return res;
}

bool doOverlap(const Bounds2D& b, float val, axis Axis)
{
    bool res;

    if(Axis == axis::xAsix)
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

