#ifndef MOUSE_H
#define MOUSE_h

#include <GLFW/glfw3.h>

class Mouse {
private:
    // Attributes
    inline static float m_deltaX = 0;
    inline static float m_deltaY = 0;
    inline static float l_PositionX = 0;
    inline static float l_PositionY = 0;
    inline static float PositionX = 1;
    inline static float PositionY = 1;
    inline static bool firstMov = 0;
    inline static bool m_buttons[GLFW_MOUSE_BUTTON_LAST] = { false };

public:
    // COnstructor and destructor
    Mouse();
    ~Mouse();

    // Callbacks
    static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    
    // Setters
    static void BlockMouseInScreen(GLFWwindow* window, bool block);
    static void StartMouse(GLFWwindow* window);
    static void EndFrame();

    // Getters
    static bool IsButtonPressed(int button);
    static float GetDeltaX();
    static float GetDeltaY();
    static float GetCurrentPosX();
    static float GetCurrentPosY();
};

#endif //MOUSE_h