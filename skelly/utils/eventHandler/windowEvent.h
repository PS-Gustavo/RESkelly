#pragma once

#include <event.h>

namespace skelly {

    class SKELLY_API WindowResizeEvent : public Event {
        public:
            WindowResizeEvent(unsigned int width, unsigned int height) : 
                m_width(width), m_height(height) {}

            inline unsigned int getWidth() const { return m_width; }
            inline unsigned int getHeight() const  { return m_height; }

            std::string toString() const override {
                std::stringstream ss;
                ss << "WindowResizeEvent: " << m_width << ", " << m_height;
                return ss.str();
            }


            EVENT_CLASS_TYPE(WindowResize)
            EVENT_CLASS_CATEGORY(EventCategoryWindow)

        private:
            unsigned int m_width, m_height;
    };

    class SKELLY_API WindowCloseEvent : public Event {
        public:
            WindowCloseEvent() {}

            //EVENT_CLASS_TYPE(WindowClose)
            EVENT_CLASS_CATEGORY(EventCategoryWindow)
    };

}