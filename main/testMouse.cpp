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
#include "interaction/mouse.hpp"

int main(int argc, char* argv[]) 
{
    // create a window
    RENDERER* render = RENDERER::getInstance();
    render->setBGColor(new COLOR(0,0,0,255));
    SDL_SetRenderDrawColor(render->getRenderer(), 255, 255, 255, 255);

    bool run = true;
    SDL_Event event;
    mouse mousebutt;
    SHAPE* new_shape = NULL;
    
    while( run)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                run = false;
            }
            
            std::pair<int, int> posMouseClick(0,0);
            if(Mouse::isMouseClick(event))
                posMouseClick = Mouse::getPosMouseClick(event, mousebutt);
            
            if(posMouseClick.first && mousebutt == mouse::leftside)
            {
                Vector3D v(posMouseClick.first, posMouseClick.second, 0);
                COLOR* c = new COLOR();
                new_shape =  Mouse::createShape(v, c, 5);
            }
            
        }
        
        if(new_shape) new_shape->render(render);

        SDL_RenderPresent(render->getRenderer()); 
        SDL_SetRenderDrawColor(render->getRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(render->getRenderer());

        SDL_SetRenderDrawColor(render->getRenderer(), 255, 255, 255, 255);
        SDL_Delay(5);


    }

    return 0;
}