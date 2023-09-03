
/****************************************************************************************
 * 
 * Lacrimal
 * Input Polling Module
 * 
 ****************************************************************************************
 * 
 * Changelog:
 * 
 * - 0.1.0: Initial implementation; Key and Mouse polling. Agnostic interface and OpenGL.
 * 
 **************************************************************************************** 
 * 
 * Description:
 * 
 * Input module allows polling whether input events are triggered or not;
 * Currently events supported are keyboard and mouse input events
 * 
 ***************************************************************************************/

#pragma once

#include <window.h>
#include <application.h>

#ifndef PCH_ENABLED
    #include <defs.h>
#endif

namespace skelly {

    class SKELLY_API Input {
        public:
            static bool isKeyPressed(int keycode) { return _s_instance->m_isKeyPressedImpl(keycode); }
            static bool isMouseButtonPressed(int button) { return _s_instance->m_isMouseButtonPressedImpl(button); }
            static float getMouseX() { return _s_instance->m_getMouseXImpl(); }
            static float getMouseY() { return _s_instance->m_getMouseYImpl(); }
            static std::pair<float, float> getMouseCoord() { return _s_instance->m_getMouseCoordImpl(); }

            static APITarget getTargetAPI() { return _s_targetAPI; }

            // agnostic creator
            static Input* create();
        protected:
            virtual bool m_isKeyPressedImpl(int keycode) = 0;
            virtual bool m_isMouseButtonPressedImpl(int button) = 0;
            virtual float m_getMouseXImpl() = 0;
            virtual float m_getMouseYImpl() = 0;
            virtual std::pair<float, float> m_getMouseCoordImpl() = 0;

        private:
            static Input* _s_instance;
            static APITarget _s_targetAPI;
    };
}