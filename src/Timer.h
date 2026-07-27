
#ifndef TIMER_H
#define TIMER_H

#include <GLFW/glfw3.h>
#include "Clock.h"

class Timer {
private:
    // Attributes
    float Elapsed;
    float _Delta;
    float ChargeTime{0};

public:
    // Constructor and Destructor
    Timer();
    ~Timer();

    // Functions
    bool Update(Clock& clock, float ms_interval);
    bool UpdateTick(Clock& clock, float ms_interval);

};

#endif
