#ifndef __SHAPE__
#define __SHAPE__

#include "particle.hpp"
#include <SDL_rect.h>

class RENDERER;
struct COLOR;
class RECTANGLE;
class SHAPE;
class CIRCLE;

/***
 * *****************************************************
 *      SHAPE
 * *****************************************************
*/

class SHAPE
{
protected:
    int id = 0;

public:
    virtual void setid(int _id) =0;
    virtual unsigned int getid() = 0;

    virtual void render(RENDERER* renderer) = 0;
    virtual void updatePos() = 0;
    virtual bool isCollided(SHAPE* otherS) = 0;

    virtual bool isCollided(RECTANGLE* rect) = 0;
    virtual bool isCollided(CIRCLE* circle) = 0;

    VECTOR getCenter() =  0;
};

/***
 * *****************************************************
 *      CIRCLE
 * *****************************************************
*/

class CIRCLE : public SHAPE, public PARTICLE
{
    int radius;
    COLOR* color;

public : 
    CIRCLE(COLOR* _color, int _radius);

    virtual void setid(int _id) override;   
    virtual unsigned int getid() override;

    virtual void render(RENDERER* renderer) override;
    virtual void updatePos() override;
    virtual bool isCollided(SHAPE* otherS) override;
    bool isCollided(RECTANGLE* rect) override;
    bool isCollided(CIRCLE* circle) override;

    VECTOR getCenter() override;
};

/***
 * *****************************************************
 *      RECTANGLE
 * *****************************************************
*/

class RECTANGLE : public SHAPE, public PARTICLE
{
    SDL_Rect rect;
    COLOR* color;

public:
    RECTANGLE(COLOR* _color, int _w, int _h);

    virtual void render(RENDERER* renderer) override;
    virtual void setid(int _id) override;
    virtual unsigned int getid() override;

    virtual void updatePos() override;
    virtual bool isCollided(SHAPE* otherS) override;

    bool isCollided(RECTANGLE* rect) override;
    bool isCollided(CIRCLE* circle) override;

    VECTOR getCenter() override;
};

#endif