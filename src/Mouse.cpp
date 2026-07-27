#include "Mouse.h"

Mouse::Mouse() 
{
}

Mouse::~Mouse() 
{
}

// Init
void Mouse::StartMouse(GLFWwindow* window) {
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
}

// Callbacks
void Mouse::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) 
{
    PositionX = static_cast<float>(xposIn);
    PositionY = static_cast<float>(yposIn);

    if (firstMov) {
        l_PositionX = PositionX;
        l_PositionY = PositionY;
        firstMov = false;
    }

    m_deltaX = PositionX - l_PositionX;
    m_deltaY = PositionY - l_PositionY;
    l_PositionX = PositionX;
    l_PositionY = PositionY;
}

void Mouse::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) 
{
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT: m_buttons[GLFW_MOUSE_BUTTON_LEFT] = -(m_buttons[GLFW_MOUSE_BUTTON_LEFT]); break;       // Button 1
        case GLFW_MOUSE_BUTTON_MIDDLE: m_buttons[GLFW_MOUSE_BUTTON_MIDDLE] = -(m_buttons[GLFW_MOUSE_BUTTON_MIDDLE]); break; // Button 2
        case GLFW_MOUSE_BUTTON_RIGHT: m_buttons[GLFW_MOUSE_BUTTON_RIGHT] = -(m_buttons[GLFW_MOUSE_BUTTON_RIGHT]); break;    // Button 3
        case GLFW_MOUSE_BUTTON_4: m_buttons[GLFW_MOUSE_BUTTON_4] = -(m_buttons[GLFW_MOUSE_BUTTON_4]); break;
        case GLFW_MOUSE_BUTTON_5: m_buttons[GLFW_MOUSE_BUTTON_5] = -(m_buttons[GLFW_MOUSE_BUTTON_5]); break;
        case GLFW_MOUSE_BUTTON_6: m_buttons[GLFW_MOUSE_BUTTON_6] = -(m_buttons[GLFW_MOUSE_BUTTON_6]); break;
        case GLFW_MOUSE_BUTTON_7: m_buttons[GLFW_MOUSE_BUTTON_7] = -(m_buttons[GLFW_MOUSE_BUTTON_7]); break;
        case GLFW_MOUSE_BUTTON_8: m_buttons[GLFW_MOUSE_BUTTON_8] = -(m_buttons[GLFW_MOUSE_BUTTON_8]); break;
    }
}

// Functions
void Mouse::BlockMouseInScreen(GLFWwindow* window, bool block) 
{
    if (block) 
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!block) 
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Mouse::EndFrame() {
    m_deltaX = 0;
    m_deltaY = 0;
}

// Getters
bool  Mouse::IsButtonPressed(int button)    { return m_buttons[button]; }
float Mouse::GetDeltaX()                    { return m_deltaX; }
float Mouse::GetDeltaY()                    { return m_deltaY; }
float Mouse::GetCurrentPosX()               { return PositionX; }
float Mouse::GetCurrentPosY()               { return PositionY; }
