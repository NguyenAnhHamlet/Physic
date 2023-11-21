#include "renderer.hpp"

RENDERER::RENDERER()
{
    window = creSDL_Window();
    renderer = creSDL_Renderer();
}

void RENDERER::creSDL_Window()
{
    SDL_Window* window = SDL_CreateWindow("SDL Ball Example", 
                                        SDL_WINDOWPOS_UNDEFINED, 
                                        SDL_WINDOWPOS_UNDEFINED, 
                                        SCREEN_WIDTH,SCREEN_HEIGHT,
                                        SDL_WINDOW_SHOWN);
    
    if (window == nullptr) 
    {
        throw WindowCreationException(SDL_GetError());
    }
}

void RENDERER::creSDL_Renderer()
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
                                                SDL_RENDERER_ACCELERATED);
    
    if (renderer == nullptr) 
    {
        throw RendererCreationException(SDL_GetError());
    }
}

void RENDERER::renderShape()
{

}

void RENDERER::addShape(SHAPE* shape)
{
    unsigned int id = takeid();
    shape->setid(id);
    Shape[id] = shape;
}

unsigned int RENDERER::takeid()
{

    int res =0;
    //check if queue is empty
    if(avail_id.Pool_ids.empty())
    {
        res = avail_id.Pool_ids.back();
        avail_id.Pool_ids.pop();
    } 
    else 
    {
        res = avail_id.max_val;
        avail_id.max_val++;
    }

    return res;
}

void RENDERER::removeShape(SHAPE* shape)
{
    if(!Shape[shape->id]) return;

    Shape.erase(shape->id);

    avail_id.Pool_ids.push(shape->id);
}