#include "gfgen.hpp"
#include "particle.hpp"
#include "pfgen.hpp"
#include "vector.hpp"
#include "shape.hpp"

GFGEN* GFGEN::gfgen = nullptr;

GFGEN::GFGEN() 
{
    gravity = VECTOR(0,convertCM(1000000),0);
}

void
GFGEN::updateForce(SHAPE* shape, float duration)
{
    shape->addForce(gravity * shape->getMass());
}