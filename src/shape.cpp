#include "shape.hpp"
#include "renderer.hpp"
#include "common.hpp"
#include <cmath>
#include "collision_hdl.hpp"

#define _USE_MATH_DEFINES

/***
 * *****************************************************
 *      RECTANGLE
 * *****************************************************
*/

RECTANGLE::RECTANGLE(COLOR* _color, int _w, int _h)
{
    this->color = _color;
    rect.w = _w;
    rect.h = _h;
    rect.x = this->pos.x - _w/2;
    rect.y = this->pos.y - _h/2;

    center = &(this->pos);

    // value of axis
    axis = hypotenuse(_w,_h)/2;
}

void 
RECTANGLE::render(RENDERER* renderer)
{
    updatePos();
    SDL_SetRenderDrawColor(renderer->getRenderer(),color->R, 
                            color->B, color->G, color->A);
    SDL_RenderFillRect(renderer->getRenderer(),&rect);
}

void 
RECTANGLE::setid(int _id)
{
    this->id = _id;
}

unsigned int 
RECTANGLE::getid()
{
    return this->id;
}

void 
RECTANGLE::updatePos()
{
    rect.x = this->pos.x;
    rect.y = this->pos.y;
}

void RECTANGLE::collideOther(COLLISION_HDL* collision_hdl)
{
    collision_hdl->collisionHDL(this);
}

float RECTANGLE::getAxisL()
{
    return axis;
}

std::vector<VECTOR*> 
RECTANGLE::getPoints()
{
    std::vector<VECTOR*> res;

    float h_w = rect.x /2;
    float h_h = rect.y /2;

    res.push_back(new VECTOR(getCenter()->x - h_w, getCenter()->y - h_h, getCenter()->z));
    res.push_back(new VECTOR(getCenter()->x + h_w, getCenter()->y - h_h, getCenter()->z));
    res.push_back(new VECTOR(getCenter()->x - h_w, getCenter()->y + h_h, getCenter()->z));
    res.push_back(new VECTOR(getCenter()->x + h_w, getCenter()->y + h_h, getCenter()->z));

    return res;
}

SDL_Rect*
RECTANGLE::getRect()
{
    return &(rect);
}

VECTOR* 
RECTANGLE::getCenter()
{
    return center;
}

float RECTANGLE::getW()
{
    return rect.w;
}

float RECTANGLE::getH()
{
    return rect.h;
}

/***
 * *****************************************************
 *      CIRCLE
 * *****************************************************
*/

CIRCLE::CIRCLE(COLOR* _color, int _radius)
{
    color = _color;
    radius = _radius;
    center = &(this->pos);
}

void 
CIRCLE::setid(int _id)
{
    this->id = _id;
}

unsigned int 
CIRCLE::getid()
{
    return this->id;
}

void 
CIRCLE::render(RENDERER* renderer)
{
    updatePos();
    SDL_SetRenderDrawColor(renderer->getRenderer(),color->R, 
                            color->B, color->G, color->A);

    for (int i = 0; i < 360; i++) 
    {
        double angle = i * 3.14159265 / 180; // Convert degrees to radians
        int x = getPos().x + radius * cos(angle);
        int y = getPos().y + radius * sin(angle);

        SDL_RenderDrawPoint(renderer->getRenderer(), x, y);
    }

    // Calculate diameter endpoints
    int dx = radius * cosf(M_PI); // offset by radius in x-axis direction
    int dy = radius * sinf(M_PI); // offset by radius in y-axis direction

    // SDL_RenderDrawLine(renderer->getRenderer(), getPos().x - dx, 
    //                     getPos().y - dy,getPos().x + dx, getPos().y + dy);
}

void 
CIRCLE::updatePos()
{
}

void 
CIRCLE::collideOther(COLLISION_HDL* collision_hdl)
{
    collision_hdl->collisionHDL(this);
}

float CIRCLE::getR()
{
    return radius;
}

VECTOR*
CIRCLE::getCenter()
{
    return center;
}


