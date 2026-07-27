#include "Clock.h"

Clock::Clock() 
{
    deltaTime = 0;
    currentTime = 0;
    lastTime = 0;
}

Clock::~Clock()
{

}

float Clock::GetDeltaTime() 
{
    return deltaTime;
}

void Clock::StartCounter() 
{
    lastTime = glfwGetTime();
}

void Clock::ProcessDelta() 
{
    currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    // Delta esta em segundos.
}

float Clock::GetFPS() 
{
    return 1.0f / deltaTime;
}

float Clock::GetMS() 
{
    return deltaTime*1000;
}