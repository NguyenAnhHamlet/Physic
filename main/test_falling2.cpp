#include "base/Vector3D.hpp"
#include "base/particle.hpp"
#include "force/particleDrag.hpp"
#include "force/particleForceRegister.hpp"
#include <list>
#include "force/pfgen.hpp"
#include <ctime>
#include <SDL.h>
#include "render/shape.hpp"
#include "render/renderer.hpp"
#include "common/common.hpp"
#include "bvh/BVH.hpp"
#include "bvh/bounds.hpp"
#include "bvh/point2D.hpp" 
#include <queue>
#include <thread>
#include "force/gfgen.hpp"

PARTICLE_FORCE_REGISTER pfreg;  
PARTICLE_DRAG* p_drag ;
GFGEN* gfgen;

int main()
{
    SHAPE* s0 =  new CIRCLE(new COLOR(255,255,255,255),20);
    s0->setPos(Vector3D(20,400,0));
    s0->setVelocity(Vector3D(100000,-10000,0));
    s0->setMass(10000);
    p_drag = new PARTICLE_DRAG(convertCM(60), convertCM(60));
    gfgen = GFGEN::getInstance();
    std::list<PFGEN*> lf;
    lf.push_back(p_drag);
    lf.push_back(gfgen);
    pfreg.add(s0,lf);

    RENDERER* render = RENDERER::getInstance();
    render->setBGColor(new COLOR(0,0,0,255));

    bool run = true;

    SDL_Event event;

    while (run)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                run = false;
            }
        }

        pfreg.updateForce(s0, 0.001);
        s0->posUpdate(s0->getVelocity(), s0->getAcceleration() ,0.001);
        s0->edgeCollide(render);
        s0->render(render);

        SDL_RenderPresent(render->getRenderer()); 
        SDL_SetRenderDrawColor(render->getRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(render->getRenderer());

        SDL_SetRenderDrawColor(render->getRenderer(), 255, 255, 255, 255);
        SDL_Delay(5);

    }

    return 0;
}