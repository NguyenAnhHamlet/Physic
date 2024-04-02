#ifndef __MOUSE__
#define __MOUSE__

#include <SDL2/SDL.h>
#include <iostream>
#include <utility>
#include "bvh/BVH.hpp"
#include "bvh/point2D.hpp"
#include "render/shape.hpp"
#include <list>

typedef enum mouse
{
    leftclick,
    rightclick,
    leftrelease,
    rightrelease
} mouse;

namespace Mouse
{
    std::pair<float,float> getPosMouseClick(SDL_Event& event, mouse click);
    std::pair<float,float> getPosMouseRelease(SDL_Event& event, mouse click);

    bool isMouseClick(SDL_Event& event,  mouse click);
    bool isMouseRelease(SDL_Event& event,  mouse click);

    // return a list of Bounds2D that intersect with the coordination
    void getBounds(BVHNode* root, std::list<Bounds2D*> listB,  std::pair<float, float> coor);

    // return a list of SHAPE that intersect with the coordination
    std::list<SHAPE*> isOnShape(std::list<Bounds2D*> b_list, std::pair<float, float> coor);

    // update pos of each SHAPE in a list to current location of mouse
    void updatePos(std::list<SHAPE*> s_list, bool update, SDL_Event &event, mouse click);

    // true if mouse coordination is on SHAPE
    int isOnShape(SHAPE* shape, std::pair<float, float> coor);

    // create BVHNode with a shape on this coordination
    BVHNode* createNode(std::pair<float, float> coor, SHAPE* s, float w, float h);
}

#endif


