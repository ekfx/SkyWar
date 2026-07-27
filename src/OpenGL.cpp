#include "OpenGL.h"

OpenGL::OpenGL()
{
    
}
OpenGL::~OpenGL()
{

}

// Cicle
void OpenGL::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void OpenGL::processInput() 
{

}

void OpenGL::GLFWConstructor() {    //Iniciar GLFW antes
    monitor = glfwGetPrimaryMonitor();      // Pega dominio do primeiro monitor.
    mode = glfwGetVideoMode(monitor);       // pega o modo de exibição do monitor
}

void OpenGL::WindowConstructor() {  // Iniciar Window antes
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
}

bool OpenGL::InitializeGLFW() {
    // Inicializando GLFW:
    if (!glfwInit()) {                                              // Verifica inicialização
        std::cout << "GLFW::FAILED_TO_INITIALIZE" << std::endl;
        return 0; 
    }                                     
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // define como versão maxima 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                  // define como versão minima 3 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // define escopo de funcoes que vamos usar
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE)           // compatibilidade com MacOS

    return 1;
}

bool OpenGL::CreateWindow(int width, int height, const char* window_name, int screen_mode) {
    if (screen_mode == ENGINE::WINDOW::BORDERLESS) {      // Borderless
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
        
        window = glfwCreateWindow(mode->width, mode->height, window_name, NULL, NULL);
    }

    if (screen_mode == ENGINE::WINDOW::FULLSCREEN)        // Fullscreen
        window = glfwCreateWindow(mode->width, mode->height, window_name, monitor, NULL); 

    if (screen_mode == ENGINE::WINDOW::WINDOWED)       // Windowed
        window = glfwCreateWindow(width, height, window_name, NULL, NULL);

    if (window == NULL) 
    {
        std::cout << "OPENGL_WINDOW::FAILED_TO_CREATE_WINDOW" << std::endl;
        glfwTerminate();    // Finaliza GLFW
        return 0;
    } else {
        std::cout << "OPENGL_WINDOW::CREATED_SUCCESSFULLY" << std::endl;
    }

    return 1;
}

bool OpenGL::MakeContext() {
    glfwMakeContextCurrent(window);     // diz para GLFW fazer o contexto
                                        // da nossa janela como o principal
                                        // do nosso processo (thread)

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD_GL_LOADER::FAILED_TO_LOAD_GLAD" << std::endl;
        return -1;
    }
    return 1;
}

bool OpenGL::RunWindow(int width, int height, const char* window_name, int screen_mode) {
    if (!InitializeGLFW())
        return 0;

    GLFWConstructor();
    
    if (screen_mode == ENGINE::WINDOW::BORDERLESS) {      // Borderless
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

        if (!CreateWindow(mode->width, mode->height, window_name, screen_mode))
            return 0;
    }

    if (screen_mode == ENGINE::WINDOW::FULLSCREEN) {      // Fullscreen
        if (!CreateWindow(mode->width, mode->height, window_name, screen_mode))
            return 0;
    }

    if (screen_mode == ENGINE::WINDOW::WINDOWED) {      // Windowed
        if (!CreateWindow(width, height, window_name, screen_mode))
            return 0;
    }

    WindowConstructor();

    if (!MakeContext())
        return 0;
    
    SetVSync(0);

    return 1;
}

GLFWwindow* OpenGL::GetWindow() {
    return window;
}

int OpenGL::GetWindowWidth() {
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    return windowWidth;
}

int OpenGL::GetWindowHeight() {
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    return windowHeight;
}

float OpenGL::GetWindowAspectRatio() {
    float t_width = GetWindowWidth();
    float t_height = GetWindowHeight();
    return t_width/t_height;
}

int OpenGL::GetFrameBufferWidth() {
    return frameBufferWidth;
}

int OpenGL::GetFrameBufferHeight() {
    return frameBufferHeight;
}

void OpenGL::SetVSync(bool enabled) {
    if (enabled) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }
}


