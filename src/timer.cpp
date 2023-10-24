#include "timer.hpp"
#include<ctime>
#include "forceVisitor.hpp"

clock_t
TIMER::getInterval(clock_t preVal)
{
    clock_t res = currentTime() - preVal;
    preVal = currentTime();

    return res;
}

void TIMER::setCallback(callbackUpdateFunc callback)
{
    this->timerCallback = callback;
}

void TIMER::countDown(PARTICLE* particle,PARTICLE_FORCE_REGISTER* p_force_reg, 
                        FORCE_VISITOR* vis,float milisecs)
{
    std::cout<< milisecs<<"RUNNING\n";
    while(1)
    {
        delay_(milisecs, preVal);
        std::cout<<"RUNNING\n";
        (particle->*timerCallback)(p_force_reg,vis,milisecs);
    }
}

std::thread* TIMER::runCountDown(PARTICLE* particle,PARTICLE_FORCE_REGISTER* p_force_reg, 
                                FORCE_VISITOR* vis, float milisecs)
{
    // countDown(particle, p_force_reg,vis , milisecs );
    std::thread* countDownThread = new std::thread(&TIMER::countDown,this, particle, p_force_reg,vis , milisecs);
    countDownThread ? (std::cout<<"NULL\n") : (std::cout<<"NOT NULL\n");
    return countDownThread;
}

TIMER::TIMER() : initVal(currentTime()), preVal(currentTime()) {};

void TIMER::delay_(float milisecs, clock_t now)
{
    while (clock() - now < milisecs);
}
