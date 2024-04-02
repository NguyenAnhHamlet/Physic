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

int n = 0;
bounds_Vector3D b_Vector3D;
set_shape_holder shape_holder; 

void render_Bound(RENDERER* render, Bounds2D* b)
{
    if (!b) return;

    SDL_RenderDrawLine(render->getRenderer(), b->getpMin().x, b->getpMin().y,
                                       b->getpMax().x, b->getpMin().y);

    SDL_RenderDrawLine(render->getRenderer(), b->getpMax().x, b->getpMin().y,
                                       b->getpMax().x, b->getpMax().y);

    SDL_RenderDrawLine(render->getRenderer(), b->getpMax().x, b->getpMax().y,
                                       b->getpMin().x, b->getpMax().y);

    SDL_RenderDrawLine(render->getRenderer(), b->getpMin().x, b->getpMax().y,
                                       b->getpMin().x, b->getpMin().y);

    if(b->getShape()) b->getShape()->render(render);
}

void render_SAH(RENDERER* render, BVHNode* root)
{
    if (!root) return;

    std::queue<BVHNode*> q;
    std::set<BVHNode*> vis;

    q.push(root);

    bool run = true;

    SDL_Event event;
    SDL_SetRenderDrawColor(render->getRenderer(), 255, 255, 255, 255);

    while (run)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                run = false;
            }
        }

        while(!q.empty())
        {

            BVHNode* node = q.front();
            render_Bound(render, node->_Bound2D);
            q.pop();

            if (node->left)
            {
                if (vis.find(node->left) == vis.end())
                {
                    q.push(node->left);
                    vis.insert(node->left);
                }
            }

            if (node->right)
            {
                if (vis.find(node->right) == vis.end())
                {
                    q.push(node->right);
                    vis.insert(node->right);
                }
            }

            SDL_RenderPresent(render->getRenderer());  
        }
    }
}



int main(int argc, char* argv[])
{
    // create a BVH node array, shape
    BVHNodeArray arr;
    

    // create multiple shape with different pos to add to array
    SHAPE* s0 =  new CIRCLE(new COLOR(255,255,255,255),20);
    SHAPE* s1 =  new CIRCLE(new COLOR(255,255,255,255),20);            
    SHAPE* s2 =  new CIRCLE(new COLOR(255,255,255,255),20);            
    SHAPE* s3 =  new CIRCLE(new COLOR(255,255,255,255),20);            
    SHAPE* s4 =  new CIRCLE(new COLOR(255,255,255,255),20);
    SHAPE* s5 =  new CIRCLE(new COLOR(255,255,255,255),20);
    SHAPE* s6 =  new CIRCLE(new COLOR(255,255,255,255),20);
    SHAPE* s7 =  new CIRCLE(new COLOR(255,255,255,255),20);
    SHAPE* s8 =  new CIRCLE(new COLOR(255,255,255,255),20);
    SHAPE* s9 =  new CIRCLE(new COLOR(255,255,255,255),20);

    // set pos for all of them 
    s0->setPos(Vector3D(20,20,0));
    s1->setPos(Vector3D(100,120,0));
    s2->setPos(Vector3D(300,160,0));
    s3->setPos(Vector3D(150,400,0));
    s4->setPos(Vector3D(200,100,0));
    s5->setPos(Vector3D(180,500,0));
    s6->setPos(Vector3D(120,300,0));
    s7->setPos(Vector3D(250,400,0));
    s8->setPos(Vector3D(300,500,0));
    s9->setPos(Vector3D(400,450,0));

    // push all of them into set holder
    shape_holder.insert(s0);
    shape_holder.insert(s1);
    shape_holder.insert(s2);
    shape_holder.insert(s3);
    shape_holder.insert(s4);
    shape_holder.insert(s5);
    shape_holder.insert(s6);
    shape_holder.insert(s7);
    shape_holder.insert(s8);
    shape_holder.insert(s9);

    // create a bound for all of them
    b_Vector3D = getBoundEach(&shape_holder);

    // take the total bound of all of them
    Bounds2D tt_b  = getBoundAll(b_Vector3D);

    // get the array of bvh node
    arr = generateBVHNodeArr(b_Vector3D);

    // creating a root node 
    BVHNode* root = rootNode(&tt_b,arr);

    // using SAH algorithm now
    SAH(arr,3,tt_b,1,1,root);

    // draw them onto the screen
    RENDERER* render = RENDERER::getInstance();
    render->setBGColor(new COLOR(0,0,0,255));

    for( auto shape : shape_holder )
        render->addShape(shape);

    render_SAH(render,root);

    return 0;
}
