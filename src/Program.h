#ifndef PROGRAM_H
#define PROGRAM_H

#include <GLAD/glad.h>   
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <glm/common.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <filesystem>
#include <fstream>
#include <map>
#include <expected>
#include <optional>
#include <memory>
#include <variant>
#include <type_traits>
#include <cstdint>

#include "Advanced.hpp"
#include "Configurator.h"
#include "Shader.h"
#include "Timer.h"
#include "Clock.h"
#include "TimerUI.h"
#include "OpenGL.h"
#include "Types.h"
#include "Mesh.h"
#include "Textures.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Camera.h"
#include "Object.h"
#include "Core.h"
#include "Sound.h"
#include "HUD.h"

class Program {
private:
    // Attributes
    std::string InfoLog;
    f32         width        = GetWindowWidth();
    f32         height       = GetWindowHeight();

    // Objects
    OpenGL      _WindowProvider;

public:
    // _ prefix refers to class objects
    Camera      _Camera;
    Clock       _Clock;
    Timer       _Timer;

    Program();
    ~Program();

    void Loop();
    void InitializeEssential();
    void Essential();
    void ProcessEssential();
    virtual bool StartMenu()                            = 0; // star menu
    virtual void InitEnvironment()                      = 0; // Inicia o ambiente com COnfiguracoes personalziadas
    virtual void Initialize()                           = 0; // inicializa RECURSOS
    virtual void Input(GLFWwindow* window, f32 Delta)   = 0; // Entrada do jogador
    virtual void ProcessPhysics(f32 Delta)              = 0; // processa fisica
    virtual void Processing()                           = 0; // processamento
    virtual void Render()                               = 0; // render
    virtual void Release()                              = 0; // Deletes

    
    // Configs
    void UpdateWindowName(bool if_run, f32 miliseconds);
    
    // Callbacks
    static void framebuffer_size_callback(GLFWwindow* window, i32 width, i32 height);
    
    // Getters
    GLFWwindow* GetWindowHandle();    
    f32 GetWindowHeight();
    f32 GetWindowWidth();
    f32 GetWindowAspectRatio();
    std::string GetInfoLog();
    
    // Setters
    void SetBackgroundColor(i32 program_color);
    void Set3D(bool on);            // desativado por padrão
    void SetRGBA();
    void SetVSync(bool off_on);     // ativado por padrão
};

#endif //PROGRAM_H
