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
#include "BVH.hpp"
#include "bounds.hpp"
#include "point2D.hpp" 

void render_Bound(RENDERER* render, Bounds2D* b)
{
    if(!b) return;

    SDL_SetRenderDrawColor(render->getRenderer(), 255, 255, 255, 255);

    SDL_RenderDrawLine(render->getRenderer(),   b->getpMin().x, b->getpMin().y,
                                                b->getpMax().x, b->getpMin().y);

    SDL_RenderDrawLine(render->getRenderer(),   b->getpMax().x , b->getpMin().y,
                                                b->getpMax().x, b->getpMax().y);

    SDL_RenderDrawLine(render->getRenderer(),   b->getpMax().x, b->getpMax().y,
                                                b->getpMin().x, b->getpMax().y);

    SDL_RenderDrawLine(render->getRenderer(),   b->getpMin().x, b->getpMax().y,
                                                b->getpMin().x, b->getpMin().y);

    // std::cout << b->getpMin().x <<'\n';
    // std::cout << b->getpMin().y <<'\n';
    // std::cout << b->getpMax().x <<'\n';
    // std::cout << b->getpMax().y <<'\n';
    // std::cout << "END"<<'\n';


}

void render_SAH(RENDERER* render, BVHNode* root)
{
    if(!root) return;

    // while (!quit) 
    // {
    //     SDL_Event event;
    //     while (SDL_PollEvent(&event)) 
    //     {
    //         if (event.type == SDL_QUIT) 
    //         {
    //             quit = true;
    //         }
    //     }

    //     // use BFS


    //     render_Bound(render, root->_Bound2D);

    // }

    render_Bound(render, root->_Bound2D);

    render_SAH(render,root->left);
    render_SAH(render, root->right);
    
}


int main(int argc, char* argv[])
{
    // create a BVH node array, shape
    BVHNodeArray arr;
    set_shape_holder shape_holder; 

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
    s0->setPos(VECTOR(20,20,0));
    s1->setPos(VECTOR(100,120,0));
    s2->setPos(VECTOR(300,160,0));
    s3->setPos(VECTOR(150,400,0));
    s4->setPos(VECTOR(200,100,0));
    s5->setPos(VECTOR(180,500,0));
    s6->setPos(VECTOR(120,300,0));
    s7->setPos(VECTOR(250,400,0));
    s8->setPos(VECTOR(300,500,0));
    s9->setPos(VECTOR(400,450,0));

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
    bounds_vector b_vector = getBoundEach(&shape_holder);

    // for (auto b : b_vector)
    // {
    //     std::cout << "Value of b_vector: " << b.getpMax().x << " " << b.getpMax().y << 'n'; 
    // } 

    // take the total bound of all of them
    Bounds2D tt_b  = getBoundAll(b_vector);

    // get the array of bvh node
    arr = generateBVHNodeArr(b_vector);

    // for( auto node : arr)
    // {
    //     // std::cout << "Value of bound: " << node->_Bound2D->getpMax().x << " " << node->_Bound2D->getpMax().y << 'n'; 
    // }

    // creating a root node 
    BVHNode* root = new BVHNode;

    // using SAH algorithm now
    SAH(arr,3,tt_b,1,1,root);


    // std::cout << tt_b.getpMax().x;

    // draw them onto the screen
    RENDERER* render = RENDERER::getInstance();
    render->setBGColor(new COLOR(0,0,0,255));

    for( auto shape : shape_holder )
        render->addShape(shape);


    render_SAH(render,root);
    render->renderShape();

    return 0;
}
