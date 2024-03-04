#include <SDL2/SDL.h>
#include <iostream>
#include "mouse.hpp"

std::namespace Mouse
{
    std::pair<float,float> getPosMouseClick(SDL_Event& event, mouse click)
    {
        int x, y;

        switch(click)
        {
            case mouse::leftclick : 
                if (event.type == SDL_MOUSEBUTTONDOWN && 
                    event.button.button == SDL_BUTTON_LEFT) 
                    {
                        SDL_GetMouseState(&x, &y);
                        std::cout << "Left mouse click at (" << x << ", " << y << ")" << std::endl;

                        return {x,y};
                    }

                break;

            case mouse::rightclick :
                if (event.type == SDL_MOUSEBUTTONDOWN && 
                    event.button.button == SDL_BUTTON_RIGHT) 
                    {
                        SDL_GetMouseState(&x, &y);
                        std::cout << "Right mouse click at (" << x << ", " << y << ")" << std::endl;

                        return {x,y};
                    }

                break;

            default:
                return {-1,-1};
        }


        return {-1,-1};
    }

    std::pair<float,float> getPosMouseRelease(SDL_Event& event, mouse click)
    {
        int x, y;

        switch(click)
        {
            case mouse::leftrelease : 
                if (event.type == SDL_MOUSEBUTTONUP && 
                    event.button.button == SDL_BUTTON_LEFT) 
                    {
                        SDL_GetMouseState(&x, &y);
                        std::cout << "Left mouse release at (" << x << ", " << y << ")" << std::endl;

                        return {x,y};
                    }

                break;

            case mouse::rightrelease :
                if (event.type == SDL_MOUSEBUTTONUP && 
                    event.button.button == SDL_BUTTON_RIGHT) 
                    {
                        SDL_GetMouseState(&x, &y);
                        std::cout << "Right mouse release at (" << x << ", " << y << ")" << std::endl;

                        return {x,y};
                    }

                break;

            default:
                return {-1,-1};
        }

        return {-1,-1};
    }

    bool isMouseClick(SDL_Event& event,  mouse click)
    {
        if(event.type == SDL_MOUSEBUTTONDOWN) return true;
        return false;
    }

    bool isMouseRelease(SDL_Event& event,  mouse click)
    {
        if(event.type == SDL_MOUSEBUTTONUP) return true;
        return false;
    }


    // return a list of Bounds2D that intersect with the coordination
    std::list<Bounds2D*> getBounds(BVHNode* root, std::pair<float, float> coor)
    {

    }

    // return a list of SHAPE that intersect with the coordination
    std::list<SHAPE*> isOnShape(std::list<Bounds2D> b_list, std::pair<float, float> coor)
    {

    }

    // update pos of each SHAPE in a list to current location of mouse
    void updatePos(std::list<SHAPE*> s_list, bool update)
    {

    }

    // true if mouse coordination is on SHAPE
    bool isOnShape(SHAPE* shape, std::pair<float, float> coor)
    {
        
    }
}