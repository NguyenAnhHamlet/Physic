#include <iostream>
#include<utility>
#include "bvh/bounds.hpp"
#include "render/shape.hpp"
#include "bvh/point2D.hpp"

bool doOverlap(const Bounds2D& b1, const Bounds2D& b2)
{
    // If one rectangle is on left side of other
    if (b1.getpMin().x > b2.getpMax().x || 
        b2.getpMin().x > b1.getpMax().x)

        return false;
 
    // If one rectangle is above other
    if (b1.getpMin().y > b2.getpMax().y ||
        b2.getpMin().y > b1.getpMax().y)
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

Bounds2D* getTotalBounds(Bounds2D* b1, Bounds2D* b2)
{
    if(!b1 && !b2 ) return NULL;
    if(!b1) return b2;
    if(!b2) return b1;
    
    point2D _pMin(  std::min(b1->getpMin().x, b2->getpMin().x), 
                    std::min(b1->getpMin().y, b2->getpMin().y));

    point2D _pMax(  std::max(b1->getpMax().x, b2->getpMax().x), 
                    std::max(b1->getpMax().y, b2->getpMax().y));

    point2D centroid(_pMin.x + _pMax.x /2, _pMin.y + _pMax.y / 2);

    return new Bounds2D(_pMin, _pMax, centroid);
}

std::pair<Bounds2D*, Bounds2D*> splitAxis(const Bounds2D& b, float xAxis , float yAxis )
{
    std::pair<Bounds2D*, Bounds2D*> res;
    point2D pMin, pMax;

    if(xAxis != -1)
    {
        res.first = new Bounds2D( b.getpMin(),point2D(xAxis, b.getpMax().y ));
        res.second = new Bounds2D( point2D(xAxis, b.getpMin().y), b.getpMax() );

    }

    if(yAxis != -1)
    {
        res.first = new Bounds2D( b.getpMin(),point2D( b.getpMax().x, yAxis ));
        res.second = new Bounds2D( point2D( b.getpMin().x, yAxis), b.getpMax() );
    }

    res.first->setCentroid();
    res.second->setCentroid();

    return res;
}

std::pair<Bounds2D*, Bounds2D*> splitAxis(const Bounds2D& b, std::pair<float, float> p_split, axis _axis )
{
    std::pair<Bounds2D*, Bounds2D*> res;
    point2D pMin, pMax;

    if(_axis == axis::xAxis)
    {
        res.first = new Bounds2D( b.getpMin(),point2D(p_split.first, b.getpMax().y ));
        res.second = new Bounds2D( point2D(p_split.second, b.getpMin().y), b.getpMax() );
    }
    else
    {
        res.first = new Bounds2D( b.getpMin(),point2D( b.getpMax().x, p_split.first ));
        res.second = new Bounds2D( point2D( b.getpMin().x, p_split.second), b.getpMax() );
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
    Bounds2D bound2D(static_cast<SHAPE*>(cir), cir->getR(), cir->getR());
    bound2D.setShape(cir);
    return bound2D;
}

Bounds2D createBound(RECTANGLE* rect)
{
    Bounds2D bound2D( static_cast<SHAPE*>(rect), rect->getW()/2, rect->getH()/2 ) ;
    bound2D.setShape(rect);
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
    setCentroid();
    setpMin();
    setpMax();
}

void
Bounds2D::init()
{
    w = pMax.x - centroid.x;
    h = pMax.y - centroid.y;
}

bool isInBounds(const Bounds2D* b, std::pair<float,float> coor)
{
    if(b->getpMin().x > coor.first || b->getpMax().x < coor.first)
        return false;
    
    if(b->getpMin().y > coor.second || b->getpMax().y < coor.second)
        return false;
    
    return true;
}

bool isInBounds(const Bounds2D* b1, const Bounds2D* b2 )
{
    if(!b1 || !b2 ) return false;

    if(b1->getpMin().x > b2->getpMax().x || b1->getpMax().x < b2->getpMin().x)
        return false;
    
    if(b1->getpMin().y >  b2->getpMax().y || b1->getpMax().y < b2->getpMin().y)
        return false;

    return true;

}
