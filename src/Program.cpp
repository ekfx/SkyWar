#include "Program.h"

void Program::framebuffer_size_callback(GLFWwindow* window, i32 width, i32 height) {
    glViewport(0, 0, width, height);
} 

Program::Program() 
{
}

Program::~Program() 
{
}

void Program::Loop() {
    _Clock.StartCounter();
    InitializeEssential();
    if (StartMenu()) {
        InitEnvironment();
        Initialize();
        while (!glfwWindowShouldClose(_WindowProvider.GetWindow())) {
            ProcessEssential();
            Processing();
            Render();
            Essential();
        }
        Release();
    }
    std::cout << (i32)glfwGetTime()/60 << "m " << (i32)glfwGetTime()%60 << "s elapsed since the program start." << std::endl;
}

void Program::Essential() {
    glfwSwapBuffers(_WindowProvider.GetWindow());   // SwapBuffer, nunca esqueça!
    glfwPollEvents();                   // Puxar Eventos, nunca esqueça!
}

void Program::ProcessEssential() {
    glClear(GL_COLOR_BUFFER_BIT);   // tem que ser definido mesmo fora do set3d
    _Clock.ProcessDelta();
    UpdateWindowName(true, 64.0f);
    Input(_WindowProvider.GetWindow(), _Clock.GetDeltaTime());
    ProcessPhysics(_Clock.GetDeltaTime());
}

void Program::InitializeEssential() 
{
    _WindowProvider.RunWindow(800, 600, "Window", ENGINE::WINDOW::WINDOWED);
    _WindowProvider.SetVSync(true);
    glfwSetFramebufferSizeCallback(_WindowProvider.GetWindow(), framebuffer_size_callback);
    
    Mouse::StartMouse(GetWindowHandle());
    Keyboard::StartKeyboard(GetWindowHandle());
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    Set3D(false);
    SetRGBA();
    
    Mouse::EndFrame();
    Mouse::BlockMouseInScreen(GetWindowHandle(), false);
}

// Configs
void Program::UpdateWindowName(bool if_run, f32 miliseconds) {
    if (if_run) {
        if (_Timer.Update(_Clock, miliseconds)) {
            glfwSetWindowTitle(GetWindowHandle(), TimerUI::GetFPSandMS(_Clock).c_str());    
        }
    }
}

// Getters
GLFWwindow* Program::GetWindowHandle() {
    return _WindowProvider.GetWindow();
};

f32 Program::GetWindowWidth() {
    return (f32)_WindowProvider.GetWindowWidth();
}

f32 Program::GetWindowHeight() {
    return (f32)_WindowProvider.GetWindowHeight();
}

f32 Program::GetWindowAspectRatio() {
    return (f32)_WindowProvider.GetWindowAspectRatio();
}

std::string Program::GetInfoLog() {
    return InfoLog;
}

void Program::SetVSync(bool off_on) {
    _WindowProvider.SetVSync(off_on);
}

// Setters
void Program::SetBackgroundColor(i32 program_color) {
    switch (program_color) {
        case ENGINE::WINDOW::RED_BACKGROUND:         glClearColor(1.0f, 0.0f, 0.0f, 1.0f); break;
        case ENGINE::WINDOW::BLUE_BACKGROUND:        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); break;
        case ENGINE::WINDOW::GREEN_BACKGROUND:       glClearColor(0.0f, 1.0f, 0.0f, 1.0f); break;
        case ENGINE::WINDOW::BLACK_BACKGROUND:       glClearColor(0.0f, 0.0f, 0.0f, 1.0f); break;
        case ENGINE::WINDOW::WHITE_BACKGROUND:       glClearColor(1.0f, 1.0f, 1.0f, 1.0f); break;
        case ENGINE::WINDOW::GRAY_BACKGROUND:        glClearColor(0.5f, 0.5f, 0.5f, 1.0f); break;
        case ENGINE::WINDOW::GRAY_WHITE_BACKGROUND:  glClearColor(0.75f, 0.75f, 0.75f, 1.0f); break; 
        case ENGINE::WINDOW::GRAY_BLACK_BACKGROUND:  glClearColor(0.25f, 0.25f, 0.25f, 1.0f); break;
        case ENGINE::WINDOW::PURPLE_BACKGROUND:      glClearColor(1.0f, 0.0f, 1.0f, 1.0f); break;
        case ENGINE::WINDOW::YELLOW_BACKGROUND:      glClearColor(1.0f, 1.0f, 0.0f, 1.0f); break;
        default: InfoLog += "INVALID_VALUE\0\0"; break;
    }
}

void Program::Set3D(bool on) {
    if (on) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST); 
    } else if (!on) {
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

void Program::SetRGBA() {
    glEnable(GL_BLEND);     // mistura de cores
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  // aceita rgba
    /*
        apenas diz que vai multiplicar a cor da imagem pelo alpha, e 
        subtrair a cor de fundo com o alpha da cor sobressalente
    */
}