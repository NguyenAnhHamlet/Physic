#ifndef __BALL_DRW__
#define __BALL_DRW__

#include <GL/glut.h>

class BallDrawer {
public:
    BallDrawer(float radius, float posX, float posY, float posZ);
    void draw(COLOR* color);

private:
    float radius;
    float posX, posY, posZ;
};

#endif