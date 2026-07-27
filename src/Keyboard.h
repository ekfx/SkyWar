#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <GLFW/glfw3.h>

class Keyboard {
private:
    // Keys
    inline static bool k_keys[GLFW_KEY_LAST] = { false };

public: 
    // Constructor and destructor
    Keyboard();
    ~Keyboard();

    // Init
    static void StartKeyboard(GLFWwindow* window);
    
    // Callbacks
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    // Getters
    static bool isKeyPressed(int key);
};

#endif // KEYBOARD_H