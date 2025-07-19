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

// setting up BVH tree and various variables
void setup(BVHNode** root, RENDERER** render)
{
    *root = rootNode(NULL);
    *render = RENDERER::getInstance();
    (*render)->setBGColor(new COLOR(0,0,0,255));
    SDL_SetRenderDrawColor((*render)->getRenderer(), 255, 255, 255, 255);
}

int main(int argc, char* argv[]) 
{
    bool run = true;
    SDL_Event event;
    mouse mousebutt;
    BVHNode* root = NULL;
    SHAPE* new_shape = NULL;
    RENDERER* render = NULL;
    BVHNodeArray nodeArr;
    BVHNode* newNode = NULL;
    PARTICLE_FORCE_REGISTER regis_force;
    GFGEN *gfgen = GFGEN::getInstance();
    int mass = 1000;
    int num = 0;

    setup(&root, &render);
    
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
            
            // there is left mouse click, create the new shape and BVHNode
            // add them into the BVH tree
            if(posMouseClick.first && mousebutt == mouse::leftside)
            {
                Vector3D v(posMouseClick.first, posMouseClick.second, 0);
                new_shape =  Mouse::createShape(v, new COLOR(), 5);
                new_shape->setMass(1000);
                newNode = new_shape->getBVHNode();
                addNode(root, newNode, 1, 1);
                regis_force.add(new_shape, gfgen);
            }
            
        }

        // update pos of each particles
        regis_force.updateForceAll(0.001);
        updatePosNode(root, render, 0.001);
        DFS(root, 1, 1);
        upgrade_Bound(root);
        upgradeBoundAll(root);

        render->renderBVH(root);

        SDL_RenderPresent(render->getRenderer()); 
        SDL_SetRenderDrawColor(render->getRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(render->getRenderer());
        SDL_SetRenderDrawColor(render->getRenderer(), 255, 255, 255, 255);
        SDL_Delay(5);
    }

    return 0;
}