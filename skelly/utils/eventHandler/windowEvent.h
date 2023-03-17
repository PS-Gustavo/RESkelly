#pragma once

#include <event.h>

namespace skelly {

    class SKELLY_API WindowResizeEvent : public Event {
        public:
            WindowResizeEvent(unsigned int width, unsigned int height) : 
                _width(width), _height(height) {}

            inline unsigned int getWidth() : const { return _width; }
            inline unsigned int getHeight() : const  { return _height; }

            std::string toString() const override {
                std::stringstream ss;
                ss << "WindowResizeEvent: " << _width << ", " << _height;
                return ss.str();
            }


            EVENT_CLASS_TYPE(WindowResize)
            EVENT_CLASS_CATEGORY(EventCategoryWindow)

        private:
            unsigned int _width, _height;
    };

    class SKELLY_API WindowCloseEvent : public Event {
        public:
            WindowCloseEvent() : {}

            EVENT_CLASS_TYPE(WindowClose)
            EVENT_CLASS_CATEGORY(EventCategoryWindow)
    };

}