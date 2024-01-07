#ifndef __CMM__
#define __CMM__

class VECTOR;

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

} COLOR;

enum class axis
{
    xAxis, 
    yAxis,
    zAxis
};

float convertCM(float pixel);

unsigned int convertPX(float meter);

unsigned int hypotenuse(float a, float b);

bool collinearPoints(VECTOR* a, VECTOR* b, VECTOR* c);



#endif