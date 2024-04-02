#ifndef __SHAPE__
#define __SHAPE__

#include "base/particle.hpp"
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
class Vector3D;
class point2D;

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
    Vector3D* center;

public:
    virtual void setid(int _id) =0;
    virtual unsigned int getid() = 0;

    virtual void render(RENDERER* renderer) = 0;
    virtual void updatePos() = 0;
    virtual void collideOther(COLLISION_HDL* collision_hdl) = 0;
    virtual void edgeCollide(RENDERER* render) = 0;

    virtual Vector3D* getCenter() = 0;
    virtual float getArea() = 0;
    virtual Vector3D support(Vector3D& direction) = 0;
    virtual Vector3D support(Vector3D&& direction) = 0;
    virtual float getR() = 0;
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
    Vector3D* center;

public : 
    CIRCLE(COLOR* _color, int _radius);
    CIRCLE();

    virtual void setid(int _id) override;   
    virtual unsigned int getid() override;

    virtual void render(RENDERER* renderer) override;
    virtual void updatePos() override;

    virtual void collideOther(COLLISION_HDL* collision_hdl) override;
    virtual void edgeCollide(RENDERER* render) override;

    Vector3D* getCenter() override;
    float getArea();

    virtual Vector3D support(Vector3D& direction) override ;
    virtual Vector3D support(Vector3D&& direction) override ;

    float getR() override;
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
    Vector3D* center;

public:
    RECTANGLE(COLOR* _color, int _w, int _h);
    RECTANGLE();

    virtual void render(RENDERER* renderer) override;
    virtual void setid(int _id) override;
    virtual unsigned int getid() override;

    virtual void updatePos() override;

    virtual void collideOther(COLLISION_HDL* collision_hdl) override;
    virtual void edgeCollide(RENDERER* render) override;

    Vector3D* getCenter() override;

    virtual Vector3D support(Vector3D&& direction) override ;
    virtual Vector3D support(Vector3D& direction) override ;

    float getAxisL();
    std::vector<Vector3D*> getPoints();
    SDL_Rect* getRect();
    float getW();
    float getH();
    float getArea();
    float getR() override;
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