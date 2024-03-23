#ifndef __CMM__
#define __CMM__

class Vector3D;

/***
 * *****************************************************
 *      RBGR COLOR
 * *****************************************************
*/
typedef struct COLOR
{
    float R;
    float B;
    float G;
    float A;

    COLOR(float _R,float _B,float _G, float _A) 
        : R(_R), B(_B), G(_G), A(_A) {}
    
    COLOR()
        : R(255) ,B(255) ,G(255) ,A(255) {}

} COLOR;

enum class axis
{
    xAxis, 
    yAxis,
    zAxis
};

float convertCM(float pixel);

unsigned int convertPX(float meter);

float hypotenuse(float a, float b);

bool collinearPoints(Vector3D* a, Vector3D* b, Vector3D* c);



#endif