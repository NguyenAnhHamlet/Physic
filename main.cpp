#include "vector.hpp"
#include "particle.hpp"
#include "particleDrag.hpp"
#include "particleForceRegister.hpp"
#include <list>
#include "pfgen.hpp"
#include <ctime>
#include <SDL.h>
#include "shape.hpp"
#include "renderer.hpp"
#include "common.hpp"

int main(int argc, char* argv[])
{
    

    return 0;
}

// int main(int argc, char* argv[])
// {
//     CIRCLE* rect = new CIRCLE(new COLOR(255,255,255,255),50);
//     rect->setMass(10.0);
//     VECTOR vector_(100, 100, 100);
//     rect->setPos(vector_);
//     VECTOR vector(10000, 0, 0);  
//     rect->setVelocity(vector);
//     PARTICLE_DRAG drag_f;
//     drag_f.setDrag(0.3,0.1);
//     PARTICLE_FORCE_REGISTER par_f_reg;
//     std::list<PFGEN*> l_f = {static_cast<PFGEN*>(&drag_f)};
//     par_f_reg.add(rect,l_f);
//     rect->autoUpdatePos(&par_f_reg,0.0001);

//     RENDERER* render = RENDERER::getInstance();
//     render->setBGColor(new COLOR(0,0,0,255));
//     render->addShape(rect);
//     render->renderShape();

//     delete rect;
//     delete render;

//     while(1){}

//     return 0;
// }


