#pragma once

#include <event.h>

namespace skelly {

    class SKELLY_API KeyEvent : public Event {
        public:
            inline int getKeyCode() const { return _key_code; }

            EVENT_CLASS_CATEGORY(EventCategoryKey | EventCategoryInput)

        protected:
            KeyEvent( int key_code ) : _key_code(key_code) {}

            int _key_code;

    };

    class SKELLY_API KeyPressedEvent : public KeyEvent {
        public:
            KeyPressedEvent(int key_code, int repeat_count)
                : KeyEvent(key_code), _repeat_count(repeat_count) {} 

            inline int GetRepeatCount() const { return _repeat_count; }

            std::string toString() const override {
                std::stringstream ss;
                ss << "KeyPressedEvent: " << _key_code << " (" << _repeat_count << " repeats)";
                return ss.str();
            }

            EVENT_CLASS_TYPE(KeyPressed)

        private:
            int _repeat_count;
    };

    class SKELLY_API KeyReleasedEvent : public KeyEvent {
        public:
            KeyReleasedEvent(int key_code) : KeyEvent(key_code) {}

            std::string toString() const override {
                std::stringstream ss;
                ss << "KeyReleasedEvent: " << _key_code;
                return ss.str();
            }

            EVENT_CLASS_TYPE(Key_Released)
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e) {
        return os << e.toString();
    }


}