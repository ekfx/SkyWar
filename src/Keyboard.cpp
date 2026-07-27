#include "Keyboard.h"

// Constructor and Destructor
Keyboard::Keyboard() 
{
}

Keyboard::~Keyboard() 
{
}

// Init 
void Keyboard::StartKeyboard(GLFWwindow* window) {
    glfwSetKeyCallback(window, key_callback);
}

// Callbacks
void Keyboard::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Array de teclas inteiro do glfw
    if (key >= 0 && key < GLFW_KEY_LAST) {
        if (action == GLFW_PRESS) {
            k_keys[key] = true;
        }
        if (action == GLFW_RELEASE) {
            k_keys[key] = false;
        }
    }
}

// Getters
bool Keyboard::isKeyPressed(int key) { 
    if (key >= 0 && key < GLFW_KEY_LAST) {
        return k_keys[key]; 
    } else { 
        return 0;
    }
}