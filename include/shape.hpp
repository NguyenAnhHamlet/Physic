#ifndef __SHAPE__
#define __SHAPE__

#include "particle.hpp"
#include <SDL_rect.h>
#include <vector>
#include <map>

class RENDERER;
struct COLOR;
class RECTANGLE;
class SHAPE;
class CIRCLE;
class COLLISION_HDL;

constexpr int _DEFAULT = 10;

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
    std::vector<int> statePool(_DEFAULT, state::NONE);

    virtual void setid(int _id) =0;
    virtual unsigned int getid() = 0;

    virtual void render(RENDERER* renderer) = 0;
    virtual void updatePos() = 0;

    virtual bool isCollided(COLLISION_HDL* collision_hdl) = 0;

    virtual void collideOther(COLLISION_HDL* collision_hdl) = 0;

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

    virtual bool isCollided(COLLISION_HDL* collision_hdl) ;
    virtual void collideOther(COLLISION_HDL* collision_hdl) ;

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

    virtual bool isCollided(COLLISION_HDL* collision_hdl) ;
    virtual void collideOther(COLLISION_HDL* collision_hdl) ;

    VECTOR getCenter() override;
};

class shape_holder
{
private:
    std::set<CIRCLE*> circle_holder;
    std::set<RECTANGLE*> rect_holder;

public:
    void addRect(RECTANGLE* rect);
    void addCircle(CIRCLE* circle);
    void removeRect(RECTANGLE* rect);
    void removeCircle(CIRCLE* circle);
};

#endif