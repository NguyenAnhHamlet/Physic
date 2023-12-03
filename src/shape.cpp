#include "shape.hpp"
#include "renderer.hpp"
#include "common.hpp"
#include <cmath>

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
    rect.x = this->pos.x;
    rect.y = this->pos.y;
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

bool 
RECTANGLE::isCollided(SHAPE* otherS)
{
    return otherS->isCollided(this);
}

bool
RECTANGLE::isCollided(RECTANGLE* rect)
{
    return 0;
}

bool 
RECTANGLE::isCollided(CIRCLE* circle)
{
    return 0;
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
    // SDL_RenderCircle(renderer->getRenderer(), getPos().x , 
    //                 getPos().y, radius);

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

    SDL_RenderDrawLine(renderer->getRenderer(), getPos().x - dx, 
                        getPos().y - dy,getPos().x + dx, getPos().y + dy);
}

void 
CIRCLE::updatePos()
{
}

bool 
CIRCLE::isCollided(SHAPE* otherS)
{
    return otherS->isCollided(this);
}

bool
CIRCLE::isCollided(RECTANGLE* rect)
{
    return 0;
}

bool 
CIRCLE::isCollided(CIRCLE* circle)
{
    return 0;
}


