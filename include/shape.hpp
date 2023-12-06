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

class SHAPE : public PARTICLE
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
    
    virtual void collideOther(SHAPE* otherS) = 0;
    virtual void collideOther(RECTANGLE* rect) = 0;
    virtual void collideOther(CIRCLE* circle) = 0;

    virtual VECTOR getCenter() = 0;
};

/***
 * *****************************************************
 *      CIRCLE
 * *****************************************************
*/

class CIRCLE : public SHAPE
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
    virtual bool isCollided(RECTANGLE* rect) override;
    virtual bool isCollided(CIRCLE* circle) override;

    virtual void collideOther() override;
    virtual void collideOther(RECTANGLE* rect) override ;
    virtual void collideOther(CIRCLE* circle) override ;


    VECTOR getCenter() override;
};

/***
 * *****************************************************
 *      RECTANGLE
 * *****************************************************
*/

class RECTANGLE : public SHAPE
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

    virtual void collideOther() override;
    virtual void collideOther(RECTANGLE* rect) override ;
    virtual void collideOther(CIRCLE* circle) override ;

    VECTOR getCenter() override;
};

#endif