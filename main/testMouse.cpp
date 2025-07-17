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
    int num = 0;

    setup(&root, &render);
    // root->_Bound2D->num= num;
    
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
                COLOR* c = new COLOR();
                new_shape =  Mouse::createShape(v, c, 5);
                newNode = new_shape->getBVHNode();
                // Bounds2D newb = createBound(new_shape);
                // newNode = initNode(&newb);
                printf("bounds : %f -- %f \n",newNode->_Bound2D->getCentroid().x, newNode->_Bound2D->getCentroid().y);
                printf("\n\n");
                num++;
                newNode->_Bound2D->num =  num;
                newNode->isPrimitive = true;
                addNode(root, newNode, 1, 1);
                // upgrade_Bound(root);
                // upgradeBoundAll(root);
                // printf("HERE 3\n");

                // while(root->left)
                // {
                //     printf("Here %p\n", root);
                //     root = root->left;
                // }
            }
            
        }

        // for(BVHNode* node : root->arr)
        // {
        //     printf("Value2 : %d && bounds : %f -- %f \n", node->_Bound2D->num, 
        //     node->_Bound2D->getCentroid().x, node->_Bound2D->getCentroid().y);
        // }

        // printf("\n\n");
        
        render->renderBVH(root);

        SDL_RenderPresent(render->getRenderer()); 
        SDL_SetRenderDrawColor(render->getRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(render->getRenderer());

        SDL_SetRenderDrawColor(render->getRenderer(), 255, 255, 255, 255);
        SDL_Delay(5);
    }

    return 0;
}