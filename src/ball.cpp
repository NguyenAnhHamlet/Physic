#include "ball.hpp"
#include "common.hpp"

BallDrawer::BallDrawer(float radius, float posX, float posY, float posZ)
        : radius(radius), posX(posX), posY(posY), posZ(posZ) {}

void 
BallDrawer::draw(COLOR* color) 
{
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glColor3f(color->R, color->B, color->G);
    glutSolidSphere(radius, 50, 50);
    glPopMatrix();
}