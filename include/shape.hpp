#ifndef __SHAPE__
#define __SHAPE__

#include "particle.hpp"
#include <SDL_rect.h>
#include <vector>
#include <map>
#include <utility>
#include <set>

class RENDERER;
struct COLOR;
class RECTANGLE;
class SHAPE;
class CIRCLE;
class COLLISION_HDL;
class shape_holder;
class VECTOR;

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
    VECTOR* center;

public:
    virtual void setid(int _id) =0;
    virtual unsigned int getid() = 0;

    virtual void render(RENDERER* renderer) = 0;
    virtual void updatePos() = 0;

    virtual void collideOther(COLLISION_HDL* collision_hdl) = 0;

    virtual VECTOR* getCenter() = 0;
    // virtual void insertThisShape(shape_holder* _shape_holder) = 0;
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
    VECTOR* center;

public : 
    CIRCLE(COLOR* _color, int _radius);

    virtual void setid(int _id) override;   
    virtual unsigned int getid() override;

    virtual void render(RENDERER* renderer) override;
    virtual void updatePos() override;

    virtual void collideOther(COLLISION_HDL* collision_hdl) override;

    VECTOR* getCenter() override;

    // virtual void insertThisShape(shape_holder* _shape_holder) override;

    float getR();
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
    float axis;
    VECTOR* center;

public:
    RECTANGLE(COLOR* _color, int _w, int _h);

    virtual void render(RENDERER* renderer) override;
    virtual void setid(int _id) override;
    virtual unsigned int getid() override;

    virtual void updatePos() override;

    virtual void collideOther(COLLISION_HDL* collision_hdl) override;

    VECTOR* getCenter() override;

    // virtual void insertThisShape(shape_holder* _shape_holder) override;

    float getAxisL();
    std::vector<VECTOR*> getPoints();
    SDL_Rect* getRect();

    float getW();
    float getH();
};

/***
 * *****************************************************
 *      shape_holder
 * *****************************************************
*/

typedef std::set<CIRCLE*> set_circle_holder ;
typedef std::set<RECTANGLE*> set_rect_holder;
typedef std::set<SHAPE*> set_shape_holder;

class shape_holder
{
    set_shape_holder* _set_shape_holder;

public:
    set_shape_holder* get_set_shape_holder() const;
    void addShape(SHAPE* s);
    void removeShape(SHAPE* s);
};

#endif