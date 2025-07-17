#include "bvh/boundBuilder.hpp"

Bound2DBuidler::Bound2DBuidler()
{
    bound2D = new Bounds2D();
    return *this;
}

BoundBuilder&
Bound2DBuidler::buildPMin(point2D pMin)
{
    bound2D.setpMin(pMin);
    return *this;
}

BoundBuilder&
Bound2DBuidler::buildPMax(point2D pMax)
{
    bound2D.setpMin(pMax);
    return *this;
}

BoundBuilder&
Bound2DBuidler::buildCentroid(point2D centroid)
{
    bound2D.setCentroid(centroid);
    return *this;
}

void 
Bound2DBuidler::buildHeight(const float heigh)
{
    bound2D.setHeight(heigh);
    return *this;
}

BoundBuilder&
Bound2DBuidler::buildWidth(float width)
{
    bound2D.setWidth(width);
    return *this;
}

BoundBuilder&
Bound2DBuidler::buildShape(SHAPE* shape)
{
    bound2D.setShape(shape);
    return *this;
}

BoundBuilder&
Bound2DBuidler::buildNumOfPrimitives(int numOfPrimitives)
{
    bound2D.setNumPrimitives(numOfPrimitives);
    return *this;
}

Bounds2D*
Bound2DBuidler::getResult()
{
    return bound2D;
}

