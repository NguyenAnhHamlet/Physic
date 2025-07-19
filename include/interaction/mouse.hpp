#ifndef __MOUSE__
#define __MOUSE__

#include <SDL2/SDL.h>
#include <iostream>
#include <utility>
#include "bvh/BVH.hpp"
#include "bvh/point2D.hpp"
#include "render/shape.hpp"
#include <list>
#include "common/timer.hpp"

typedef enum mouse
{
    leftside = 1,
    rightside = 2
} mouse;

namespace Mouse
{
    // return the coordinate of the mouse click
    std::pair<float,float> getPosMouseClick(SDL_Event& event, mouse& click);
    // return the coordinate of the mouse release
    std::pair<float,float> getPosMouseRelease(SDL_Event& event, mouse& release);

    bool isMouseClick(SDL_Event& event);
    bool isMouseRelease(SDL_Event& event);

    // return a list of Bounds2D that intersect with the coordination
    void getBounds(BVHNode* root, std::list<Bounds2D*> listB,  std::pair<float, float> coor);

    // return a list of SHAPE that intersect with the coordination
    std::list<SHAPE*> isOnShape(std::list<Bounds2D*> b_list, std::pair<float, float> coor);

    // update pos of each SHAPE in a list to current location of mouse
    void updatePos(std::list<SHAPE*> s_list, bool update, SDL_Event &event, mouse click);

    // true if mouse coordination is on SHAPE
    int isOnShape(SHAPE* shape, std::pair<float, float> coor);

    // create BVHNode on this coordination
    // w : the width of the bound
    // h : high of the bound 
    BVHNode* createNode(std::pair<float, float> coor, SHAPE* s, 
                        float w =0, float h =0);

    // create a shape on this position of mouse click
    SHAPE* createShape(Vector3D& coor, COLOR* color, 
                       float r =0, float w =0, float h =0); 

    /**
     *  1. disable currently applying force, calculating/storing new forces during dragging
     *  2. Calculate these new forces applied upon object during dragging
     *  3. Apply these force back to object
     * 
     *  F = m.a 
     *  m is available
     *  a = (v1 - v0)/(t1 - t0)
     *  (t1 -t0) is available
     *  v0 = 0 (at the beginning of the dragging)
     *  v1 = (s1 - s0)/ (t1 - t0)
     *  (s1 - s0) is available
     *  Final : F = m.((s1 - s0)/(t1-t0) - v0)/(t1 - t0)
     *  F is only the average force apply on the object
     *  when mouse got release but it is good enough 
     *  for the engine   
     */

    std::list<PFGEN*> mouseDragging(SHAPE* shape, TIMER* timer);
}

#endif


