#ifndef CLOCK_H
#define CLOCK_H

#include <GLFW/glfw3.h>

class Clock {
private:
    // Attributes
    float deltaTime;
    double currentTime;
    double lastTime;

public:
    // Constructor and Destructor
    Clock();
    ~Clock();

    // Functions
    float GetMS();
    float GetFPS();
    float GetDeltaTime();
    void StartCounter();
    void ProcessDelta();

};

#endif //CLOCK_H