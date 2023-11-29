#include "common.hpp"

float convertCM(float pixel)
{
    return (pixel/37.795);
}

unsigned int convertPX(float meter)
{
    return (meter * 100 * 37.795);
}