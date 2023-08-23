
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
 * This is the specification for events involving keys. The focal class KeyEvent stores the
 * keycode affected, and the subclasses define what action was made to that key.
 * 
 ***************************************************************************************/

#pragma once

#include <event.h>

namespace skelly {

    inline std::ostream& operator<<(std::ostream& os, const Event& e) {
        return os << e.toString();
    }

    class SKELLY_API KeyEvent : public Event {
        public:
            inline int getKeyCode() const { return m_keyCode; }

            EVENT_CLASS_CATEGORY(EventCategoryKey | EventCategoryInput)

        protected:
            KeyEvent( int key_code ) : m_keyCode(key_code) {}

            int m_keyCode;

    };

    class SKELLY_API KeyPressedEvent : public KeyEvent {
        public:
            KeyPressedEvent(int key_code, int repeat_count)
                : KeyEvent(key_code), _m_repeatCount(repeat_count) {} 

            inline int GetRepeatCount() const { return _m_repeatCount; }

            std::string toString() const override {
                std::stringstream ss;
                ss << "KeyPressedEvent: " << m_keyCode << " (" << _m_repeatCount << " repeats)";
                return ss.str();
            }

            EVENT_CLASS_TYPE(KeyPressed)

        private:
            int _m_repeatCount;
    };

    class SKELLY_API KeyReleasedEvent : public KeyEvent {
        public:
            KeyReleasedEvent(int key_code) : KeyEvent(key_code) {}

            std::string toString() const override {
                std::stringstream ss;
                ss << "KeyReleasedEvent: " << m_keyCode;
                return ss.str();
            }

            EVENT_CLASS_TYPE(KeyReleased)
    };

    class SKELLY_API KeyTypedEvent : public KeyEvent {
        public:
            KeyTypedEvent(unsigned short character) : KeyEvent((int) character) {}

            std::string toString() const override {
                std::stringstream ss;
                ss << "KeyReleasedEvent: " << m_keyCode;
                return ss.str();
            }

            EVENT_CLASS_TYPE(KeyTyped)
    };
}