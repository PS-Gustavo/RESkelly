#include <imguiLayer.h>

namespace skelly {

    ImguiLayer::ImguiLayer() : Layer("ImguiLayer") {

    }

    ImguiLayer::~ImguiLayer() {

    }

    // bool ImguiLayer::imguiResolveWindowClose() {return false;}
    // bool ImguiLayer::imguiResolveWindowResize() {return false;}
    // bool ImguiLayer::imguiResolveWindowFocus() {return false;}
    // bool ImguiLayer::imguiResolveWindowLostFocus() {return false;}
    // bool ImguiLayer::imguiResolveWindowMoved() {return false;}
    bool ImguiLayer::imguiResolveKeyPressed(KeyPressedEvent& event) {
        return false;
    }
    bool ImguiLayer::imguiResolveKeyReleased(KeyReleasedEvent& event) {
        return false;
    }
    bool ImguiLayer::imguiResolveMouseButtonPressed(MouseButtonPressedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseButtonEvent(event.getMouseButton(), true);
        return false;
    }
    bool ImguiLayer::imguiResolveMouseButtonReleased(MouseButtonReleasedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseButtonEvent(event.getMouseButton(), false);
        return false;
    }
    bool ImguiLayer::imguiResolveMouseScrolled(MouseScrolledEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseWheelEvent(event.getXOffset(), event.getYOffset());
        return false;
    }
    bool ImguiLayer::imguiResolveMouseMoved(MouseMovedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.AddMousePosEvent(event.getX(), event.getY());
        return false;
    }

    void ImguiLayer::onEvent(Event& event) {

        EventDispatcher dispatcher(event);
        DISPATCH_BINDER(MouseButtonPressedEvent, ImguiLayer::imguiResolveMouseButtonPressed);
        DISPATCH_BINDER(MouseButtonReleasedEvent, ImguiLayer::imguiResolveMouseButtonReleased);
        DISPATCH_BINDER(MouseMovedEvent, ImguiLayer::imguiResolveMouseMoved);
        DISPATCH_BINDER(MouseScrolledEvent, ImguiLayer::imguiResolveMouseScrolled);
        DISPATCH_BINDER(KeyPressedEvent, ImguiLayer::imguiResolveKeyPressed);
        DISPATCH_BINDER(KeyReleasedEvent, ImguiLayer::imguiResolveKeyReleased);
        
        // to be implemented, if necessary
        // DISPATCH_BINDER(WindowResizeEvent, ImguiLayer::imguiResolveWindowResize);
        // DISPATCH_BINDER(WindowResizeEvent, ImguiLayer::imguiResolveWindowClose);
        // DISPATCH_BINDER(WindowResizeEvent, ImguiLayer::imguiResolveWindowFocus);
        // DISPATCH_BINDER(WindowResizeEvent, ImguiLayer::imguiResolveWindowLostFocus);
        // DISPATCH_BINDER(WindowResizeEvent, ImguiLayer::imguiResolveWindowMoved);
    }

    void ImguiLayer::onAttach() {
        
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        ImGui::SetNextWindowSize(ImVec2(400, 300));
        ImGui::SetNextWindowPos(ImVec2(200, 200));
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;         
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        ImGui::StyleColorsDark();

        Application& app = Application::getApplication();
        
        ImGui_ImplOpenGL3_Init("#version 130");
        
        // setWindow(&app.getWindow());
    }

    void ImguiLayer::onUpdate() {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::getApplication();
        GLFWwindow* window = glfwGetCurrentContext();

        int w, h;
        int display_w, display_h;
        glfwGetWindowSize(window, &w, &h);
        glfwGetFramebufferSize(window, &display_w, &display_h);

        io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());
        if (w > 0 && h > 0) io.DisplayFramebufferScale = ImVec2((float)display_w / (float)w, (float)display_h / (float)h);

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