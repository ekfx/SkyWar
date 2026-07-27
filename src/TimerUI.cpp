#include "TimerUI.h"

TimerUI::TimerUI()
{
}

TimerUI::~TimerUI()
{
}

std::string TimerUI::GetFPSandMS(Clock& clock) 
{
    float _delta = clock.GetDeltaTime();
    
    if (_delta > 0.0f ) {
        return "FPS: " + std::to_string((int)(1.0f / _delta)) + 
            " | " + 
            "MS: " + std::to_string(_delta*1000);
    } else {
        return "FPS: 0 | MS: 0";
    }
}

/*
if (timer.Update(myClock, 64.0f)) {
    title = TimerUI::GetFPSandMS(myClock);
    glfwSetWindowTitle(ogl.GetWindow(), title.c_str());
}
            */