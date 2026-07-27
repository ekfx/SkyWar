#ifndef TIMERUI_H
#define TIMERUI_H

#include <string>
#include "Clock.h"

class TimerUI {
private:

public:
    // Constructor and Destructor
    TimerUI();
    ~TimerUI();

    // Functions
    static std::string GetFPSandMS(Clock& clock);
};

#endif //TIMERUI_H
