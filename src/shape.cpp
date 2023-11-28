#include "shape.hpp"
#include "renderer.hpp"
#include "common.hpp"

RECTANGLE::RECTANGLE(COLOR* _color, int _w, int _h)
{
    this->color = _color;
    rect.w = _w;
    rect.h = _h;
    rect.x = this->pos.x;
    rect.y = this->pos.y;
}

void RECTANGLE::render(RENDERER* renderer)
{
    updatePos();
    SDL_SetRenderDrawColor(renderer->getRenderer(),color->R, color->B, color->G, color->A);
    SDL_RenderFillRect(renderer->getRenderer(),&rect);
}

void RECTANGLE::setid(int _id)
{
    this->id = _id;
}

unsigned int RECTANGLE::getid()
{
    return this->id;
}

void RECTANGLE::updatePos()
{
    rect.x = this->pos.x;
    rect.y = this->pos.y;
}