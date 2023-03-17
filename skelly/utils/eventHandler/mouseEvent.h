#pragma once

#include <event.h>

namespace skelly {

    class SKELLY_API MouseMovedEvent : public Event {
        public:
            MouseMovedEvent(float x, float y) : _mouse_x(x), _mouse_y(y) {}

            inline float getX() const { return _mouse_x; }
            inline float getY() const { return _mouse_y; }

            std::string toString() const override {
                std::stringstream ss;
                ss << "MouseMovedEvent: " << _mouse_x << ", " << _mouse_y;
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseMoved);
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
        
        private:
            float _mouse_x, _mouse_y;
    };

    class SKELLY_API MouseScrolledEvent : public Event {
        public:
            MouseScrolledEvent(float x_offset, float y_offset) :
                _x_offset(x_offset), _y_offset(y_offset) {}

            inline float getXOffset() const { return _x_offset; }
            inline float getYOffset() const { return _y_offset; }

            std::string toString() const override {
                std::stringstream ss;
                ss << "MouseScrolledEvent: " << getXOffset() << ", " << getYOffset();
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseScrolledEvent)
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

        private:
            float _x_offset, _y_offset;
    };

    class SKELLY_API MouseButtonEvent : public Event {
        public:
            inline int getMouseButton() const { return _button; }

            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

        protected:
            MouseButtonEvent(int button) : _button(button) {}
            int _button;
    };

    class SKELLY_API MouseButtonPressedEvent : public MouseButtonEvent {
        public:
            MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

            std::string toString() const override {
                std::stringstream ss;
                ss << "MouseButtonPressedEvent: " << _button;
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseButtonPressedEvent)
    };

    class SKELLY_API MouseButtonReleasedEvent : public MouseButtonEvent {
        public:
            MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

            std::string toString() const override {
                std::stringstream ss;
                ss << "MouseButtonReleasedEvent: " << _button;
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseButtonReleasedEvent)
    };

}