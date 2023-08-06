#pragma once

#include <application.h>

#define IMGUI_IMPL_API
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#ifndef PCH_ENABLED
    #include <layer.h>
    #include <mouseEvent.h>
    #include <keyEvent.h>
    #include <windowEvent.h>
    #include <keyBindings.h>
    #include <mouseBindings.h>
#endif

namespace skelly {

    class SKELLY_API ImguiLayer : public Layer {
        public:
            ImguiLayer();
            ~ImguiLayer();

            virtual void onAttach() override;
            virtual void onDetach() override;
            virtual void onImguiRender() override;

            static void imguiOverlayPane(bool* p_open);

            void begin();
            void end();

            inline void setWindow(Window* window) { _m_window = window; }
            inline Window* getWindow() { return _m_window; }

        private:
            float _m_time = 0.0f;
            Window* _m_window = nullptr;

    };

}