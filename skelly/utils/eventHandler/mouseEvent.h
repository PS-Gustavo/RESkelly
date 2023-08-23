
/****************************************************************************************
 * 
 * Temporal
 * Events Module
 * 
 ****************************************************************************************
 * 
 * Changelog:
 * 
 * - 0.1.0: Initial implementation; Basic event handling, key, mouse and window handlers
 * 
 **************************************************************************************** 
 * 
 * Description:
 * 
 * This is the specification for events involving the mouse. The classes store the position
 * information, buttons pressed or other relevant information.
 * 
 ***************************************************************************************/

#pragma once

#include <event.h>

namespace skelly {

    class SKELLY_API MouseMovedEvent : public Event {
        public:
            MouseMovedEvent(float x, float y) : _m_mouseX(x), _m_mouseY(y) {}

            inline float getX() const { return _m_mouseX; }
            inline float getY() const { return _m_mouseY; }

            std::string toString() const override {
                std::stringstream ss;
                ss << "MouseMovedEvent: " << _m_mouseX << ", " << _m_mouseY;
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseMoved);
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
        
        private:
            float _m_mouseX, _m_mouseY;
    };

    class SKELLY_API MouseScrolledEvent : public Event {
        public:
            MouseScrolledEvent(float x_offset, float y_offset) :
                _m_xOffset(x_offset), _m_yOffset(y_offset) {}

            inline float getXOffset() const { return _m_xOffset; }
            inline float getYOffset() const { return _m_yOffset; }

            std::string toString() const override {
                std::stringstream ss;
                ss << "MouseScrolledEvent: " << getXOffset() << ", " << getYOffset();
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseScrolled)
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

        private:
            float _m_xOffset, _m_yOffset;
    };

    class SKELLY_API MouseButtonEvent : public Event {
        public:
            inline int getMouseButton() const { return m_button; }

            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

        protected:
            MouseButtonEvent(int button) : m_button(button) {}
            int m_button;
    };

    class SKELLY_API MouseButtonPressedEvent : public MouseButtonEvent {
        public:
            MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

            std::string toString() const override {
                std::stringstream ss;
                ss << "MouseButtonPressedEvent: " << m_button;
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class SKELLY_API MouseButtonReleasedEvent : public MouseButtonEvent {
        public:
            MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

            std::string toString() const override {
                std::stringstream ss;
                ss << "MouseButtonReleasedEvent: " << m_button;
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseButtonReleased)
    };

}