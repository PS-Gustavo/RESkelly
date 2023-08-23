
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
 * This is the specification for events involving the window. Classes in this section deal
 * with the resizing and closing actions.
 * 
 ***************************************************************************************/

#pragma once

#include <event.h>

namespace skelly {

    class SKELLY_API WindowResizeEvent : public Event {
        public:
            WindowResizeEvent(unsigned int width, unsigned int height) : 
                _m_width(width), _m_height(height) {}

            inline unsigned int getWidth() const { return _m_width; }
            inline unsigned int getHeight() const  { return _m_height; }

            std::string toString() const override {
                std::stringstream ss;
                ss << "WindowResizeEvent: " << _m_width << ", " << _m_height;
                return ss.str();
            }


            EVENT_CLASS_TYPE(WindowResize)
            EVENT_CLASS_CATEGORY(EventCategoryWindow)

        private:
            unsigned int _m_width, _m_height;
    };

    class SKELLY_API WindowCloseEvent : public Event {
        public:
            WindowCloseEvent() = default;

            EVENT_CLASS_TYPE(WindowClose)
            EVENT_CLASS_CATEGORY(EventCategoryWindow)
    };

}