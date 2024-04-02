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
<<<<<<< HEAD
bounds_vector b_vector; 
=======
bounds_Vector3D b_Vector3D;
>>>>>>> f643c6cccabf372d6914e417cd8a5ae3c37bb2a5
set_shape_holder shape_holder; 
BVHNode* node = NULL;
 // create a BVH node array, shape
BVHNodeArray arr;

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

void render_BVH(RENDERER* render, BVHNode* root)
{
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

        if (!root) return;

        // std::queue<BVHNode*> q;
        // std::set<BVHNode*> vis;

        // q.push(root);

        upgrade_Bound(root);
        upgradeBoundAll(root);
        DFS(root,1,1);

        for(auto s : shape_holder)
        {
            s->posUpdate(s->getVelocity(),0.005);
            s->edgeCollide(render);
            s->render(render);
        }
        // for(auto node : arr) 
        //     render_Bound(render,node->_Bound2D);

        // render_BVH(render,root);

        SDL_RenderPresent(render->getRenderer()); 
        SDL_SetRenderDrawColor(render->getRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(render->getRenderer());

        SDL_SetRenderDrawColor(render->getRenderer(), 255, 255, 255, 255);
        SDL_Delay(5);

        // while(!q.empty())
        // {

        //     BVHNode* node = q.front();
        //     render_Bound(render, node->_Bound2D);
        //     q.pop();

        //     if (node->left)
        //     {
        //         if (vis.find(node->left) == vis.end())
        //         {
        //             q.push(node->left);
        //             vis.insert(node->left);
        //         }
        //     }

        //     if (node->right)
        //     {
        //         if (vis.find(node->right) == vis.end())
        //         {
        //             q.push(node->right);
        //             vis.insert(node->right);
        //         }
        //     }

        //     SDL_RenderPresent(render->getRenderer()); 
         
        // }
    }
}



int main(int argc, char* argv[])
{
    
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

    // set velocity
    s0->setVelocity(Vector3D(100,100,0));
    s1->setVelocity(Vector3D(200,200,0));
    s2->setVelocity(Vector3D(-150,150,0));
    s3->setVelocity(Vector3D(-200,-200,0));

    s0->setid(0);
    s1->setid(1);
    s2->setid(2);
    s3->setid(3);
    s4->setid(4);
    s5->setid(5);
    s6->setid(6);
    s7->setid(7);
    s8->setid(8);
    s9->setid(9);

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


    for( auto s : shape_holder)
    {
        s->setMass(100);
    }

    // create a bound for all of them
<<<<<<< HEAD
    b_vector = getBoundEach(&shape_holder);

    // take the total bound of all of them
    Bounds2D tt_b  = getBoundAll(b_vector);

    // get the array of bvh node
    arr = generateBVHNodeArr(b_vector);
=======
    b_Vector3D = getBoundEach(&shape_holder);

    // take the total bound of all of them
    Bounds2D tt_b  = getBoundAll(b_Vector3D);

    // get the array of bvh node
    arr = generateBVHNodeArr(b_Vector3D);
>>>>>>> f643c6cccabf372d6914e417cd8a5ae3c37bb2a5

    // creating a root node 
    BVHNode* root = rootNode(&tt_b,arr);

    // using SAH algorithm now
    SAH(arr,3,tt_b,1,1,root,1);

    // draw them onto the screen
    RENDERER* render = RENDERER::getInstance();
    render->setBGColor(new COLOR(0,0,0,255));

    render_BVH(render,root);

    return 0;
}
