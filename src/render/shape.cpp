#include "render/shape.hpp"
#include "render/renderer.hpp"
#include "common/common.hpp"
#include <cmath>
#include "collision/collision_hdl.hpp"
#include <math.h>
#include "bvh/point2D.hpp"
<<<<<<< HEAD
#include "base/Vector3D.hpp"
=======
#include "base/Vector3D"
>>>>>>> f643c6cccabf372d6914e417cd8a5ae3c37bb2a5

#define _USE_MATH_DEFINES

/***
 * *****************************************************
 *      RECTANGLE
 * *****************************************************
*/

RECTANGLE::RECTANGLE(COLOR* _color, int _w, int _h)
{
    this->color = _color;
    rect.w = _w;
    rect.h = _h;
    rect.x = this->pos.x - _w/2;
    rect.y = this->pos.y - _h/2;

    center = &(this->pos);

    // value of axis
    axis = hypotenuse(_w,_h)/2;
}

RECTANGLE::RECTANGLE()
{
    this->color = new COLOR();
    rect.w = 0;
    rect.h = 0;
<<<<<<< HEAD
    rect.x = this->pos.x;
    rect.y = this->pos.y;
=======
    rect.x = this->pos.x - _w/2;
    rect.y = this->pos.y - _h/2;
>>>>>>> f643c6cccabf372d6914e417cd8a5ae3c37bb2a5

    center = &(this->pos);
}

void 
RECTANGLE::render(RENDERER* renderer)
{
    updatePos();
    SDL_SetRenderDrawColor(renderer->getRenderer(),color->R, 
                            color->B, color->G, color->A);
    SDL_RenderFillRect(renderer->getRenderer(),&rect);
}

void 
RECTANGLE::setid(int _id)
{
    this->id = _id;
}

unsigned int 
RECTANGLE::getid()
{
    return this->id;
}

void 
RECTANGLE::updatePos()
{
    rect.x = this->pos.x;
    rect.y = this->pos.y;
}

void RECTANGLE::collideOther(COLLISION_HDL* collision_hdl)
{
    collision_hdl->collisionHDL(this);
}

float RECTANGLE::getAxisL()
{
    return axis;
}

std::vector<Vector3D*> 
RECTANGLE::getPoints()
{
    std::vector<Vector3D*> res;

    float h_w = rect.x /2;
    float h_h = rect.y /2;

    res.push_back(new Vector3D(getCenter()->x - h_w, getCenter()->y - h_h, getCenter()->z));
    res.push_back(new Vector3D(getCenter()->x + h_w, getCenter()->y - h_h, getCenter()->z));
    res.push_back(new Vector3D(getCenter()->x - h_w, getCenter()->y + h_h, getCenter()->z));
    res.push_back(new Vector3D(getCenter()->x + h_w, getCenter()->y + h_h, getCenter()->z));

    return res;
}

SDL_Rect*
RECTANGLE::getRect()
{
    return &(rect);
}

Vector3D* 
RECTANGLE::getCenter()
{
    return center;
}

float RECTANGLE::getW()
{
    return rect.w;
}

float RECTANGLE::getH()
{
    return rect.h;
}

float 
RECTANGLE::getArea()
{
    return getW() * getH();
}

void 
RECTANGLE::edgeCollide(RENDERER* render)
{
    std::pair<unsigned int, unsigned int> WH = render->getWH();
    Vector3D pos = getPos();

    if(getPos().x - rect.w /2 <= 0 || getPos().x + rect.w / 2 >= WH.first )
    {
        pos.x - rect.w /2 <= 0 ? setPos(Vector3D(rect.w /2  ,pos.y, pos.z)) : setPos(Vector3D(WH.first - rect.w /2 , pos.y, pos.z));
        setVelocity(Vector3D(getVelocity().x * -1, getVelocity().y, getPos().z));
    }

    if(getPos().y - rect.h /2 <= 0 || getPos().y + rect.h / 2 >= WH.second )
    {
        pos.y - rect.h /2 <= 0 ? setPos(Vector3D(pos.x, rect.h /2, pos.z)) : setPos(Vector3D(pos.x, WH.second - rect.h /2, pos.z));
        setVelocity(Vector3D(getVelocity().x , getVelocity().y * -1, getPos().z));
    }
}

Vector3D
<<<<<<< HEAD
RECTANGLE::support(Vector3D& direction)
=======
RECTANGLE::support(Vector3D* direction)
>>>>>>> f643c6cccabf372d6914e417cd8a5ae3c37bb2a5
{
    float furthestDistance = FLT_MIN;
    Vector3D* furthestVertex = NULL;

    std::vector<Vector3D*> vertices = getPoints();

    for(Vector3D* v : vertices) 
    {
        float distance = v->scalarProduct(direction);
        if(distance > furthestDistance) {
            furthestDistance = distance;
            furthestVertex = v;
        }
    }

<<<<<<< HEAD
    return std::move(*furthestVertex);
}

Vector3D
RECTANGLE::support(Vector3D&& direction)
{
    float furthestDistance = FLT_MIN;
    Vector3D* furthestVertex = NULL;

    std::vector<Vector3D*> vertices = getPoints();

    for(Vector3D* v : vertices) 
    {
        float distance = v->scalarProduct(direction);
        if(distance > furthestDistance) {
            furthestDistance = distance;
            furthestVertex = v;
        }
    }

    return std::move(*furthestVertex);
=======
    return furthestVertex;
>>>>>>> f643c6cccabf372d6914e417cd8a5ae3c37bb2a5
}


float RECTANGLE::getR()
{
    return hypotenuse(getH(), getW());
}

/***
 * *****************************************************
 *      CIRCLE
 * *****************************************************
*/

CIRCLE::CIRCLE(COLOR* _color, int _radius)
{
    color = _color;
    radius = _radius;
    center = &(this->pos);
}

CIRCLE::CIRCLE()
{
    color  = new COLOR();
    radius = 0;
    center = &(this->pos);
}

void 
CIRCLE::setid(int _id)
{
    this->id = _id;
}

unsigned int 
CIRCLE::getid()
{
    return this->id;
}

void 
CIRCLE::render(RENDERER* renderer)
{
    updatePos();
    SDL_SetRenderDrawColor(renderer->getRenderer(),color->R, 
                            color->B, color->G, color->A);
    
    int offsetx, offsety, d;
    int status;
    int x, y, radius;

    x = getPos().x;
    y = getPos().y;
    radius = getR();

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer->getRenderer(), x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer->getRenderer(), x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer->getRenderer(), x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer->getRenderer(), x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }
}

void 
CIRCLE::updatePos()
{
}

void 
CIRCLE::collideOther(COLLISION_HDL* collision_hdl)
{
    collision_hdl->collisionHDL(this);
}

float CIRCLE::getR()
{
    return radius;
}

Vector3D*
CIRCLE::getCenter()
{
    return center;
}

float 
CIRCLE::getArea()
{
    return M_PI * getR();
}

void 
CIRCLE::edgeCollide(RENDERER* render)
{
    std::pair<unsigned int, unsigned int> WH = render->getWH();
    Vector3D pos = getPos();

    if(pos.x - getR() <= 0 || pos.x + getR() >= WH.first )
    {
        pos.x - getR() <= 0 ? setPos(Vector3D(getR() , pos.y, pos.z)) : setPos(Vector3D(WH.first - getR(), pos.y, pos.z));
        setVelocity(Vector3D(getVelocity().x * -1, getVelocity().y, pos.z));
    }

    if(pos.y - getR() <= 0 || pos.y + getR() >= WH.second )
    {
        pos.y - getR() <= 0 ? setPos(Vector3D(pos.x, getR() , pos.z)) : setPos(Vector3D(pos.x, WH.second - getR(), pos.z));
        setVelocity(Vector3D(getVelocity().x , getVelocity().y * -1, pos.z));
    }
}

<<<<<<< HEAD
Vector3D
CIRCLE::support(Vector3D& direction)
{
    Vector3D center = *getCenter();
    return (center + direction.normalize() * getR());
}

Vector3D
CIRCLE::support(Vector3D&& direction)
{
    Vector3D center = *getCenter();
    return (center + direction.normalize() * getR());
}




=======
Vector3D* 
CIRCLE::support(Vector3D* direction)
{
    return getCenter() + direction.normalized() * getR();
}


>>>>>>> f643c6cccabf372d6914e417cd8a5ae3c37bb2a5
