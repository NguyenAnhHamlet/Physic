#include "timer.hpp"

clock_t
TIMER::getInterval(clock_t preVal)
{
    clock_t res = currentTime() - preVal;
    preVal = currentTime();

    return res;
}

void TIMER::setCallback( callbackFunc callback)
{
    this->timerCallback = callback;
}

void TIMER::countDown(PARTICLE* particle,clock_t milisecs)
{
    while(1)
    {
        delay_(milisecs, preVal);
        (particle->*timerCallback)();
    }
}

void TIMER::runCountDown(PARTICLE* particle,clock_t milisecs)
{
    std::thread countDownThread(&TIMER::countDown,this, particle, milisecs);
    countDownThread.join();
}

TIMER::TIMER() : initVal(currentTime()), preVal(currentTime()) {};

void TIMER::delay_(clock_t milisecs, clock_t now)
{
    while (clock() - now < milisecs);
}
