#include "render/renderer.hpp"
#include "common/common.hpp"
#include "render/shape.hpp"

RENDERER* RENDERER::render = nullptr;

RENDERER::RENDERER(unsigned int w, unsigned int h)
{
    creSDL_Window(w,h);
    creSDL_Renderer();
}

void 
RENDERER::creSDL_Window(unsigned int w , unsigned int h )
{
    width = w;
    height = h;

    window = SDL_CreateWindow(  "SDL Ball Example", 
                                SDL_WINDOWPOS_UNDEFINED, 
                                SDL_WINDOWPOS_UNDEFINED, 
                                w,h,
                                SDL_WINDOW_SHOWN);
    
    if (window == nullptr) 
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }
}

void 
RENDERER::creSDL_Renderer()
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    
    if (renderer == nullptr) 
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    }
}

void 
RENDERER::renderShape()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Event event;

    while (this->run)
    {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                run = 0;
            }
        }

        SDL_RenderClear(renderer);

        for(auto it : Shape)
        {
            renderShape(it.second);
            SDL_SetRenderDrawColor( renderer, background->R, background->B,
                                    background->G, background->A);
            SDL_RenderPresent(renderer);
        }
    }
}

void 
RENDERER::renderShape(SHAPE* shape)
{
    shape->render(this);
}

void 
RENDERER::addShape(SHAPE* shape)
{
    unsigned int id = takeid();
    shape->setid(id);
    Shape[id] = shape;
}

unsigned int 
RENDERER::takeid()
{
    int res =0;

    //check if queue is empty
    if(!avail_id.Pool_ids.empty())
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

void 
RENDERER::removeShape(SHAPE* shape)
{
    if(!Shape[shape->getid()]) return;

    Shape.erase(shape->getid());

    avail_id.Pool_ids.push(shape->getid());
}

void 
RENDERER::setBGColor(COLOR* BGColor)
{
    this->background = BGColor;
}

SDL_Renderer* RENDERER::getRenderer() { return this->renderer;}

SDL_Window* RENDERER::getWindow() { return this->window; }

COLOR* RENDERER::getBGColor() { return this->background;}

RENDERER::~RENDERER()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void 
RENDERER::setWidth(unsigned int w)
{
    width = w;
}

void 
RENDERER::setHeight(unsigned int h)
{
    height = h;
}

std::pair<unsigned int, unsigned int> 
RENDERER::getWH()
{
    return {width,height};
}

void 
RENDERER::renderBVH(BVHNode* root, float duration)
{
    // DFS to render shape in each node
    
    // Edge case
    if(!root ) return;

    // render shape
    if(!root->isroot && root->_Bound2D->getShape() )
    {
        root->_Bound2D->getShape()->posUpdate(root->_Bound2D->getShape()->getVelocity(), duration);
        root->_Bound2D->getShape()->edgeCollide(this);
        root->_Bound2D->getShape()->render(this);
    } 

    renderBVH(root->left, duration);
    renderBVH(root->right, duration);
}