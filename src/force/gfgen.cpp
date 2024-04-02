#include "force/gfgen.hpp"
#include "base/particle.hpp"
#include "force/pfgen.hpp"
#include "base/Vector3D.hpp"
#include "render/shape.hpp"

GFGEN* GFGEN::gfgen = nullptr;

GFGEN::GFGEN() 
{
    gravity = Vector3D(0,convertCM(1000000),0);
}

void
GFGEN::updateForce(SHAPE* shape, float duration)
{
    shape->addForce(gravity * shape->getMass());
}