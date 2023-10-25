#ifndef __TIMER__
#define __TIMER__


#include <iostream>
#include<ctime>
#include <thread>
#include <assert.h>
#include <vector>

class PARTICLE;
class PARTICLE_FORCE_REGISTER;
class FORCE_VISITOR;

/**
 * Mainly use to keep calculate the interval between the updation
 * of position of a particle
 *
 * One to one, each particle has its own timer
*/


class TIMER
{
    // Keep the time when the object is created
    clock_t initVal;

public:
    /**
     * This is a typedef of a callback function which is used
     * with this timer class
    */
    typedef void (PARTICLE::*callbackUpdateFunc)(PARTICLE_FORCE_REGISTER*,FORCE_VISITOR* , float);

    /**
     * In case one want to use the object with the method of its
     * to update the position of a particle , one can use this value
     * to store the previous time in which the position of that
     * particle is updated
     *
     * Default value is set to initVal
    */
    clock_t preVal;

    callbackUpdateFunc timerCallback;

    TIMER();

    void setInitVal(clock_t val) {initVal = val; };
    clock_t  getInitVal() {return initVal; };

    clock_t currentTime() { return clock();};

    // delay , block the thread or process for a duration of time
    void delay_(float milisecs, clock_t now);
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
    void setCallback(callbackUpdateFunc callback);

    void countDown(PARTICLE* particle,PARTICLE_FORCE_REGISTER* p_force_reg, 
                   FORCE_VISITOR* vis,float milisecs);

    std::thread* runCountDown(PARTICLE* particle, 
                                PARTICLE_FORCE_REGISTER* p_force_reg, 
                                FORCE_VISITOR* vis, float milisecs);
};

#endif // __TIMER__
