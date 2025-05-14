#include <SDL2/SDL.h>
#include <iostream>
#include "interaction/mouse.hpp"
#include "bvh/bounds.hpp"
#include "bvh/BVH.hpp"
#include "gjk/gjk.hpp"
#include "render/shapeFactory.hpp"

namespace Mouse
{
    std::pair<float,float> getPosMouseClick(SDL_Event& event, mouse& click)
    {
        int x, y;

        if (event.type == SDL_MOUSEBUTTONDOWN && 
            event.button.button == SDL_BUTTON_LEFT) 
        {
            SDL_GetMouseState(&x, &y);
            click = mouse::leftside;
            std::cout << "Left mouse click at (" << x << ", " << y << ")" << std::endl;

            return {x,y};
        }

        else if (event.type == SDL_MOUSEBUTTONDOWN && 
            event.button.button == SDL_BUTTON_RIGHT) 
        {
            SDL_GetMouseState(&x, &y);
            click == mouse::rightside;
            std::cout << "Right mouse click at (" << x << ", " << y << ")" << std::endl;

            return {x,y};
        }

        else 
            return {-1,-1};
    }

    std::pair<float,float> getPosMouseRelease(SDL_Event& event, mouse& release)
    {
        int x, y;

        if (event.type == SDL_MOUSEBUTTONUP && 
            event.button.button == SDL_BUTTON_LEFT) 
        {
            SDL_GetMouseState(&x, &y);
            release = mouse::leftside;
            std::cout << "Left mouse release at (" << x << ", " << y << ")" << std::endl;

            return {x,y};
        }

        else if (event.type == SDL_MOUSEBUTTONUP && 
            event.button.button == SDL_BUTTON_RIGHT) 
        {
            SDL_GetMouseState(&x, &y);
            release = mouse::rightside;
            std::cout << "Right mouse release at (" << x << ", " << y << ")" << std::endl;

                return {x,y};
        }

        else
            return {-1,-1};
        
    }

    bool isMouseClick(SDL_Event& event)
    {
        std::cout <<"Func isMouseClick run\n" << '\n';
        if(event.type == SDL_MOUSEBUTTONDOWN) 
        {
            std::cout << "Mouse clicked\n" << '\n';
            
            return true;
        }
        return false;
    }

    bool isMouseRelease(SDL_Event& event)
    {
        if(event.type == SDL_MOUSEBUTTONUP) return true;
        return false;
    }


    // return a list of Bounds2D that intersect with the coordination
    void getBounds( BVHNode* root, std::list<Bounds2D*> listB,  
                    std::pair<float, float> coor)
    {
        // root is NULL, do nothing
        if(!root ) return;

        // only those bounds which intersect with coor 
        // will be continued with the search
        if(isInBounds(root->_Bound2D, coor))
        {   
            // in case this is not a leave node, continue down
            if(root->_Bound2D->getShape() == NULL) 
            {
                getBounds(root->left, listB, coor);
                getBounds(root->right, listB, coor);
            }
            else 
            {
                // found leave node that intersect with coor, 
                // add it to listB
                listB.push_back(root->_Bound2D);
            }
        }
    }

    // return a list of SHAPE that intersect with the coordination
    std::list<SHAPE*> isOnShape(std::list<Bounds2D*> b_list, 
                                std::pair<float, float> coor)
    {
        std::list<SHAPE*> res;

        for(auto b : b_list)
        {
            if(isOnShape( b->getShape(), coor))
                res.push_back(b->getShape());
        }

        return res;
    }

    // update pos of each SHAPE in a list to current location of mouse
    void updatePos( std::list<SHAPE*> s_list, bool update, 
                    SDL_Event &event, mouse click)
    {
        std::pair<float, float> pos2D = getPosMouseClick(event, click);
        for(auto s : s_list)
        {
            if(pos2D.first != -1 && pos2D.second != -1)
                s->setPos(Vector3D(pos2D.first, pos2D.second, 0));

        }
    }

    // true if mouse coordination is on SHAPE
    int isOnShape(SHAPE* shape, std::pair<float, float> coor)
    {
        CIRCLE* tmpC = new CIRCLE();
        tmpC->setPos(Vector3D(coor.first, coor.second, 0));
        std::vector<Vector3D> vertices;
        Vector3D direction;
        while(1)
        {
            switch (evolveSimplex(shape, tmpC, vertices, direction))
            {
                case EvolveResult::StillEvolving:
                    break;

                case EvolveResult::NoIntersection:
                    if(tmpC) delete tmpC;
                    return 0;
                
                case EvolveResult::FoundIntersection:
                    if(tmpC) delete tmpC;
                    return 1;

                default:
                    if(tmpC) delete tmpC;
                    return -1;
            }
        }

        // there is problem happen 
        if(tmpC) delete tmpC;
        return -1;
    }

    BVHNode* createNode(std::pair<float, float> coor, SHAPE* s, 
                        float w, float h)
    {
        if(coor.first == -1 &&  coor.second == -1) return NULL;
        s->setPos(Vector3D(coor.first, coor.second, 0));
        BVHNode* newNode = initNode(new Bounds2D(s,w,h));

        return newNode;
    }

    SHAPE* createShape(Vector3D& coor, COLOR* color, 
                       float r, float w, float h)
    {
        if(r > 0) 
            return ShapeFactory::createShape(coor, color, r);
        if(w > 0 && h > 0) 
            return ShapeFactory::createShape(coor, color, w, h);
        else 
            return NULL;
    }
}