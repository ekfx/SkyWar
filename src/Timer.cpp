#include "Timer.h"
#include <iostream>

Timer::Timer() 
{
    Elapsed = 0;
}

Timer::~Timer()
{

}

bool Timer::Update(Clock& clock, float ms_interval) 
{
    bool triggered = false;

    _Delta = clock.GetDeltaTime() * 1000.0f;
    Elapsed = Elapsed + _Delta;

    while (Elapsed >= ms_interval) {
        Elapsed = Elapsed - ms_interval;
        triggered = true;
    }
    
    return triggered;
}

bool Timer::UpdateTick(Clock& clock, float ms_interval) 
{
    ms_interval /= 1000;
    ChargeTime += clock.GetDeltaTime();

    if (ChargeTime >= ms_interval) {
        ChargeTime = 0;
        return true;
    }

    return false;
}
