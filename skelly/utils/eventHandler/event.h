#pragma once

#include <defs.h>

namespace skelly {

    // WIP: Change event system from blocking to buffering
    // WIP: Develop different processing stages for the project

    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        KeyPressed, KeyReleased,
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
        
        protected:
            bool m_isHandled = false;
    };

    class EventDispatcher {
        template<typename T>
        using EventFn = std::function<bool(T&)>;

        public:
            EventDispatcher(Event& event) : m_event(event) {}

            template<typename T>
            bool dispatch(EventFn<T> func) {
                if(m_event.getEventType() == T::getStaticType()) {
                    m_event.m_isHandled == func(*(T*)&m_event);
                    return true;
                }
                return false;
            }

        private:
            Event& m_event;

    };
}