#ifndef __CMM__
#define __CMM__

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

/***
 * *****************************************************
 *      state
 * *****************************************************
*/
typedef enum state
{
    CHECKED = 1,
    UNCHECKED = 0,
    NONE = -1
} state;

float convertCM(float pixel);

unsigned int convertPX(float meter);


#endif