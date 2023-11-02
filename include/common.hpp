#ifndef __CMM__
#define __CMM__

// RBG color
typedef struct COLOR
{
    float R;
    float B;
    float G;

    COLOR(float _R,float _B,float _G) 
        : R(_R), B(_B), G(_G) {}

} COLOR;


#endif