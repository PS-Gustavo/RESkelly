
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
 * This is the generic implementation for event handling. It contains the basic structure
 * for event identification, as well as the dispatcher to the correct handlers based on
 * 3 subsets of events: key, mouse or window events.
 * 
 ***************************************************************************************/

#pragma once

#ifndef PCH_ENABLED
    #include <defs.h>
    #include <iostream>
    #include <sstream>
    #include <functional>
#endif

namespace skelly {

    // WIP: Change event system from blocking to buffering
    // WIP: Develop different processing stages for the project

    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory {
        None = 0,
        EventCategoryWindow = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKey = BIT(2),
        EventCategoryMouse = BIT(3)
    };

    class SKELLY_API Event {

        friend class EventDispatcher;

        public:
            virtual EventType getEventType() const = 0;
            virtual const char* getName() const = 0;
            virtual int getCategoryFlags() const = 0;
            virtual std::string toString() const { return getName(); }

            inline bool IsInCategory(EventCategory category) {
                return getCategoryFlags() & category;
            }

            bool isHandled() const { return m_isHandled; }

        protected:
            bool m_isHandled = false;
    };

    // The dispatcher receives a function with a parameter of type T. If T matches the type
    // of the event, event is set as handled as its handler is called.
    class EventDispatcher {
        template<typename T>
        // EventFn receives T and returns bool
        using EventFn = std::function<bool(T&)>;

        public:
            EventDispatcher(Event& event) : _m_event(event) {}

            template<typename T>
            bool dispatch(EventFn<T> func) {
                if(_m_event.getEventType() == T::getStaticType()) {
                    _m_event.m_isHandled = func(*(T*)&_m_event);
                    return true;
                }
                return false;
            }

        private:
            Event& _m_event;
    };
}