#include <imguiLayer.h>

namespace skelly {

    ImguiLayer::ImguiLayer() : Layer("ImguiLayer") {

    }

    ImguiLayer::~ImguiLayer() {

    }

    void ImguiLayer::onEvent(Event& event) {

    }

    void ImguiLayer::onAttach() {
        // ImGui::CreateContext();
        // ImGui::StyleColorsDark();

        // ImGuiIO& io = ImGui::GetIO();
        // io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        // io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        // // io.AddKeyEvent(ImGuiMod_Ctrl,  (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS));
        // // io.AddKeyEvent(ImGuiMod_Shift, (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)   == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)   == GLFW_PRESS));
        // // io.AddKeyEvent(ImGuiMod_Alt,   (glfwGetKey(window, GLFW_KEY_LEFT_ALT)     == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_ALT)     == GLFW_PRESS));
        // // io.AddKeyEvent(ImGuiMod_Super, (glfwGetKey(window, GLFW_KEY_LEFT_SUPER)   == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_SUPER)   == GLFW_PRESS));

        // ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void ImguiLayer::onUpdate() {
        // ImGuiIO& io = ImGui::GetIO();
        // Application& app = Application::getApplication();
        // io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

        // float time = (float)glfwGetTime();
        // io.DeltaTime = _m_time > 0.0f ? (time - _m_time) : (1.0f / 60.0f);
        // _m_time = time;

        // ImGui_ImplOpenGL3_NewFrame();
        // ImGui::NewFrame();

        // static bool show = true;
        // ImGui::ShowDemoWindow(&show);

        // ImGui::Render();
        // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
    }

    void ImguiLayer::onDetach() {

    }

}