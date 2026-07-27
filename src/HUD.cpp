#include "HUD.h"

HUD::HUD() {

}
HUD::~HUD() {
    
}

void HUD::SetCustomStyleFunction(std::function<void()> custom_style_function_lambda) {
    /*
        ImGuiStyle& Style = ImGui::GetStyle();
		float aspect_ratio 	= GetWindowHeight() / GetWindowWidth();
		float pos_height 	= 10.0f;
		float pos_width 	= 10.0f;
		float height 		= 10.0f;
		float width 		= 10.0f;

		ImGui::SetNextWindowPos(ImVec2((GetWindowHeight()/(aspect_ratio*pos_width)), (GetWindowWidth()/(aspect_ratio*pos_height))));
		ImGui::SetNextWindowSize(ImVec2((GetWindowWidth()/(aspect_ratio*width)), (GetWindowHeight()/(aspect_ratio*height))));
		Style.FontScaleMain = 1.25f;
    */
    callback_custom_style = custom_style_function_lambda;
}

void HUD::SetCustomRenderFunction(std::function<void()> custom_render_function_lambda) {
    callback_custom_render = custom_render_function_lambda;
}

void HUD::Start(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);     // inicializa para opengl
    ImGui_ImplOpenGL3_Init("#version 330");
}

void HUD::Run(float window_width, float window_height, bool debug_window) {
    float aspect_ratio = window_width/window_height;
    float hud_width = (window_width/100)*15;
    float hud_height = (window_height/100)*50;
    ImVec2 pos = ImVec2(10, 10);

    if (callback_custom_render) {
        if (!ActivedHUD) return;    // termina funcao

        ImGuiStyle& HUDStyle = ImGui::GetStyle();
        // HUDStyle.Colors[ImGuiCol_Border] = ImVec4(0.0, 0.0f, 0.0f, 0.0f);
        // HUDStyle.Colors[ImGuiCol_WindowBg] = ImVec4(0.25, 0.0f, 0.0f, 0.4f);
        // HUDStyle.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.7, 0.0f, 0.0f, 0.0f);
        // HUDStyle.Colors[ImGuiCol_TitleBg] = ImVec4(0.7, 0.0f, 0.0f, 0.8f);
        // HUDStyle.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.7, 0.0f, 0.0f, 0.8f);
        // HUDStyle.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.7, 0.0f, 0.0f, 0.8f);
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        ImGui::SetNextWindowPos(pos);
        ImGui::SetNextWindowSize(ImVec2(hud_width, hud_height));
        
        if (callback_custom_style) {
            callback_custom_style();
            /*
                ImGuiStyle& HUDStyle = ImGui::GetStyle();
                ImGui::SetNextWindowPos(positon);
                ImGui::SetNextWindowSize(ImVec2(hud_width, hud_height));
            */
        }

        callback_custom_render();

        if (debug_window) { 
            ImGui::ShowStyleEditor(); 
            ImGui::ShowMetricsWindow(); 
        }

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    } else {
        infoLog += "HUD::NOT_DEFINED_CALLBACK_FUNCTION\n";
    }
}

void HUD::Release() {
    if (ImGui::GetCurrentContext() != nullptr) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}