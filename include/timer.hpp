#ifndef __TIMER__
#define __TIMER__


#include <iostream>
#include<ctime>
#include <thread>
#include <assert.h>
#include <vector>
#include"particle.hpp"

/**
 * Mainly use to keep calculate the interval between the updation
 * of position of a particle
 *
 * One to one, each particle has its own timer
*/

/**
 * This is a typedef of a callback function which is used
 * with this timer class
*/
typedef void (PARTICLE::*callbackFunc)();

class TIMER
{
    // Keep the time when the object is created
    clock_t initVal;

public:
    /**
     * In case one want to use the object with the method of its
     * to update the position of a particle , one can use this value
     * to store the previous time in which the position of that
     * particle is updated
     *
     * Default value is set to initVal
    */
    clock_t preVal;

    callbackFunc timerCallback;

    TIMER() : initVal(currentTime()), preVal(currentTime())
    {};

    void setInitVal(clock_t val) {initVal = val; };
    clock_t  getInitVal() {return initVal; };

    clock_t currentTime() { return clock();};

    // delay , block the thread or process for a duration of time
    void delay_(clock_t milisecs, clock_t now)
        { while (clock() - now < milisecs)};

    /**
     * get the interval between current time and previous time
     * then update the value of previous time
    */
    clock_t getInterval(clock_t preVal);

    /**
     * Keep runnning in seperate thread, when timout this will
     * automatically call callback func that is set in setCallBack
     * function
     *
     * In case one doesn't want to use getInterval with updatePos
     * to update the position of a particle, one could choose
     * to use this countDown with callback function to update
     * the position of the particle in the exact amount of
     * period of time
    */
    void setCallback(callbackFunc callback);
    void countDown(PARTICLE* particle, clock_t milisecs);
    void runCountDown(PARTICLE* particle,clock_t milisecs);
}

#endif // __TIMER__
