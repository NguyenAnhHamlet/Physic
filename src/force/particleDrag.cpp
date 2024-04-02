#include "force/particleDrag.hpp"
#include "base/particle.hpp"
#include "force/pfgen.hpp"
#include "base/Vector3D.hpp"
#include "render/shape.hpp"

PARTICLE_DRAG::PARTICLE_DRAG(float _dragCoeff , float _density )
                : dragCoeff(_dragCoeff), density(_density)
                {}


void 
PARTICLE_DRAG::setDragCoeff(float _dragCoeff)
{
    dragCoeff = _dragCoeff;
}

void
PARTICLE_DRAG::setDensity(float _density)
{
    density = _density;
}
        
void 
PARTICLE_DRAG::updateForce(SHAPE* shape, float duration)
{
    Vector3D force = shape->getVelocity() * shape->getVelocity() * 
                   1/2 * density * dragCoeff * shape->getArea();

    Vector3D vel = shape->getVelocity();
    Vector3D invert_dir = Vector3D( vel.x != 0 ?  vel.x/abs(vel.x) : 0, 
                                vel.y != 0 ?  vel.y/abs(vel.y) : 0,
                                vel.z != 0 ?  vel.z/abs(vel.z) : 0) * -1 ;

    shape->addForce(force  * invert_dir);
}
