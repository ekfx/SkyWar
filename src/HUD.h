#ifndef HUD_H
#define HUD_H

#include <GLAD/glad.h>   
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <functional>
#include <string>

class HUD {
private:    
    bool ActivedHUD = 1;
    std::string infoLog;
    std::function<void()> callback_custom_render;
    std::function<void()> callback_custom_style;
    /*
        isso é uma funcao lambda, void() diz o tipo, 
        std::function é o tipo que ela tem e é definido
        pela biblioteca <functional>

        neste caso, essa instancia é uma cópia para
        um função que está por vir, ela será
        anonima (lambda), copiada e rechamada pelo nosso programa,
        fazendo com que o programador possa reescrever 
        sua propria funcao e ser chamada aqui.

        Exemplo:
        MyHUD.SetCustomRenderFunction([&](){
            ImGui::Begin();
            ImGui::End();
        })

        [](){}; definem um lambda, sendo [] o escopo de variaveis em que
        ele está, () os parametros de função comum, e {} como o escopo da 
        função. É semelhante a uma função do javascript.
        [&] significa que pode pegar as variaveis do escopo onde for escrita
        como uma função qualquer, há diversos outros tipos, como [variavel]
        que voce dita qual variavel pode pegar, [=] que pega todas do escopo
        (útil para varreduras).

        Grande utilidade do lambda: é uma função anonima, e com o 
        std::function (um conteiner para lambda), voce pode "armazenar" o
        codigo da função e fazer callbacks.
    */

public:
    HUD();
    ~HUD();

    void SetCustomRenderFunction(std::function<void()> custom_render_function_lambda);
    void SetCustomStyleFunction(std::function<void()> custom_style_function_lambda);
    void Start(GLFWwindow* window);
    void Run(float window_width, float window_height, bool debug_window);
    void Release();

};

#endif // HUD_H