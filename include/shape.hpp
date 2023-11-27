#ifndef __SHAPE__
#define __SHAPE__

#include "particle.hpp"
#include <SDL_rect.h>

class RENDERER;
struct COLOR;

class SHAPE : public PARTICLE
{
protected:
    int id = 0;
public:
    virtual void setid(int _id) =0;
    virtual unsigned int getid() = 0;
    virtual void render(RENDERER* renderer) = 0;
};

// class CIRCLE : public SHAPE
// {
//     int radius;
//     COLOR* color;

// public : 
//     CIRCLE(COLOR* _color, int _radius);
//     virtual void render(RENDERER* renderer) override;
// };

class RECTANGLE : public SHAPE 
{
    SDL_Rect rect;
    COLOR* color;

public:
    RECTANGLE(COLOR* _color, int _w, int _h);
    virtual void render(RENDERER* renderer) override;
    virtual void setid(int _id) override;
    virtual unsigned int getid();
};

#endif