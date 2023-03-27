#pragma once

#include <event.h>

namespace skelly {

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

    inline std::ostream& operator<<(std::ostream& os, const Event& e) {
        return os << e.toString();
    }


}