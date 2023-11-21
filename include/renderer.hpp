#ifndef __RENDERER__
#define __RENDERER__

#include <SDL.h>
#include <list>
#include "shape.hpp"
#include <map>
#include <queue>

/**
 * implement singleton here, allow only one renderer to 
 * render all of shape inside a map
 * 
 * Only one renderer in one process
*/

class RENDERER
{
    RENDERER();
    static RENDERER* render;

    // deleting copy constructor
    RENDERER(const RENDERER& render)= delete; 

    // deleting assign operator
    RENDERER& operator=(const GFGEN&) = delete;

    /**
     * a map store all shape to be rendered onto window
     * 
     * Just like linux operating system use file descriptor 
     * to keep track of process. This render will have a DSA 
     * to keep all of available interger ready to be assigned 
     * to each of shape. 
     * 
     * User can then delete the shape from map with only the 
     * interger associated with thus shape. Thus the shape also 
     * have to bear the infos regarding for the interger it takes 
     * inside Shape map.
    */
    std::map<int,SHAPE*> Shape;

    /**
     * The ideal is simple with this data structure
     * 
     * Keep one interger max_val. This will keep track 
     * of the maximum value of current fd. 
     * When user delete the shape from map, the interger 
     * now is free for use. To keep this, a queue or stack 
     * is needed. So when user try to add new shape into 
     * map. There are 2 options:
     * 
     * 1. Check is queue is empty or not, if not then take 
     * the tail value of queue and pop the fd out. 
     * 2. If queue is empty, simply take current value of 
     * max_val and increase it by 1.
     * 
     * typedef a struct to be more easy to use
    */ 
    typedef struct Avail_ids
    {
        unsigned int max_val = 0;
        std::queue<int> Pool_ids;
    } avail_ids;

    Avail_ids avail_id; 

    // window and renderer
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    static RENDERER* getInstance()
    {
        if( !render) render = new RENDERER();
        return render;
    }

    void creSDL_Window();
    void creSDL_Renderer();

    // render all shape inside map onto the screen
    void renderShape();

    // add new shape into map
    void addShape(SHAPE* shape);

    // take the available fd and return it
    unsigned int takeid();

    void removeShape(SHAPE* shape);

};

#endif

