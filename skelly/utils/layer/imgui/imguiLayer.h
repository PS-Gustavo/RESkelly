#pragma once

#include <skelly.h>
#include <render.h>

#ifndef PCH_ENABLED
    #include <layer.h>
    #include <mouseEvent.h>
    #include <keyEvent.h>
    #include <windowEvent.h>
#endif

namespace skelly {

    class SKELLY_API ImguiLayer : public Layer {
        public:
            ImguiLayer();
            ~ImguiLayer();

            void onAttach();
            void onDetach();
            void onUpdate();
            void onEvent(Event& event);

            inline void setWindow(Window* window) { _m_window = window; }
            inline Window* getWindow() { return _m_window; }

        private:
            float _m_time = 0.0f;
            Window* _m_window = nullptr;

            bool imguiResolveWindowClose();
            bool imguiResolveWindowResize();
            bool imguiResolveWindowFocus();
            bool imguiResolveWindowLostFocus();
            bool imguiResolveWindowMoved();
            bool imguiResolveKeyPressed();
            bool imguiResolveKeyReleased();
            bool imguiResolveMouseButtonPressed(MouseButtonPressedEvent& event);
            bool imguiResolveMouseButtonReleased(MouseButtonReleasedEvent& event);
            bool imguiResolveMouseScrolled(MouseScrolledEvent& event);
            bool imguiResolveMouseMoved(MouseMovedEvent& event);

    };

}