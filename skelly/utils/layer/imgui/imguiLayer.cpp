#include <imguiLayer.h>

namespace skelly {

    ImguiLayer::ImguiLayer() : Layer("ImguiLayer") {

    }

    ImguiLayer::~ImguiLayer() {

    }

    void ImguiLayer::onEvent(Event& event) {

    }

    void ImguiLayer::onAttach() {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        ImGui::StyleColorsDark();

        Application& app = Application::getApplication();

        ImGui_ImplOpenGL3_Init("#version 130");
    }

    void ImguiLayer::onUpdate() {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::getApplication();
        io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

        float time = (float)glfwGetTime();
        io.DeltaTime = _m_time > 0.0f ? (time - _m_time) : (1.0f / 60.0f);
        _m_time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
    }

    void ImguiLayer::onDetach() {

    }

}