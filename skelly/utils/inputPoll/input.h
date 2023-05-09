#pragma once

#include <window.h>
#include <application.h>
#include <GLFW/glfw3.h>

namespace skelly {

    class SKELLY_API Input {
        public:
            inline static bool isKeyPressed(int keycode) { return _s_instance->m_isKeyPressedImpl(keycode); }
            inline static bool isMouseButtonPressed(int button) { return _s_instance->m_isMouseButtonPressedImpl(button); }
            inline static float getMouseX() { return _s_instance->m_getMouseXImpl(); }
            inline static float getMouseY() { return _s_instance->m_getMouseYImpl(); }
            inline static std::pair<float, float> getMouseCoord() { return _s_instance->m_getMouseCoordImpl(); }

        protected:
            virtual bool m_isKeyPressedImpl(int keycode) = 0;
            virtual bool m_isMouseButtonPressedImpl(int button) = 0;
            virtual float m_getMouseXImpl() = 0;
            virtual float m_getMouseYImpl() = 0;
            virtual std::pair<float, float> m_getMouseCoordImpl() = 0;

        private:
            static Input* _s_instance;
    };

    class PlatInput : public Input {
        protected:
            bool m_isKeyPressedImpl(int keycode) override;
            bool m_isMouseButtonPressedImpl(int button) override;
            float m_getMouseXImpl() override;
            float m_getMouseYImpl() override;
            std::pair<float, float> m_getMouseCoordImpl() override;
    } ;

}

#ifdef PLATFORM_LINUX
#endif