#include "common/timer.hpp"
#include <ctime>

clock_t
TIMER::getInterval(clock_t preVal)
{
    clock_t res = currentTime() - preVal;
    preVal = currentTime();

    return res;
}

void 
TIMER::setCallback(callbackUpdateFunc callback)
{
    this->timerCallback = callback;
}

void 
TIMER::countDown(PARTICLE* particle,PARTICLE_FORCE_REGISTER* p_force_reg, 
                float milisecs)
{
    while(1)
    {
        delay_(milisecs, preVal);
        (particle->*timerCallback)(p_force_reg,milisecs);
    }
}

std::thread* 
TIMER::runCountDown(PARTICLE* particle,PARTICLE_FORCE_REGISTER* p_force_reg, 
                            float milisecs)
{
    std::thread* countDownThread = new std::thread(&TIMER::countDown,this, particle, p_force_reg, milisecs);
    return countDownThread;
}

TIMER::TIMER() : initVal(currentTime()), preVal(currentTime()) {};

void 
TIMER::delay_(float milisecs, clock_t now)
{
    while (clock() - now < milisecs);
}

void TIMER::static_delay(float milisecs, clock_t now)
{
    while (clock() - now < milisecs);
}
