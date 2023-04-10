#pragma once


#include <GLFW/glfw3.h>
#include <logger.h>

#ifndef PCH_ENABLED
    #include <defs.h>
    #include <string>
    #include <functional>
    #include <windowEvent.h>
    #include <mouseEvent.h>
    #include <keyEvent.h>
#endif

// Platform agnostic section
namespace skelly {

    struct WindowProps {
        std::string title;
        unsigned int width;
        unsigned int height;

        WindowProps(const std::string& title = "RESkelly",
            unsigned int width = 1280,
            unsigned int height = 720
        ) : title(title), width(width), height(height) {}
    };

    class SKELLY_API Window {
        public:
            using EventCallbackFn = std::function<void(Event&)>;

            virtual ~Window() {}

            virtual void onUpdate() = 0;

            virtual unsigned int getWidth() const = 0;
            virtual unsigned int getHeight() const = 0;

            virtual void setEventCallback(const EventCallbackFn& callback) = 0;
            virtual void setVSync(bool enabled) = 0;
            virtual bool isVSync() const = 0;

            static Window* create(const WindowProps& props = WindowProps());
    };
}

#ifdef PLATFORM_WINDOWS
#endif

#ifdef PLATFORM_LINUX

namespace skelly {
    class LinuxWindow : public Window {
        public:
            LinuxWindow(const WindowProps& props);
            virtual ~LinuxWindow();

            void onUpdate() override;

            inline unsigned int getWidth() const override { return m_data.width; }
            inline unsigned int getHeight() const override { return m_data.height; }

            inline void setEventCallback(const EventCallbackFn& callback) 
                override { m_data.eventCallback = callback; }
            void setVSync(bool enabled) override;
            bool isVSync() const override;

        private:
            virtual void init(const WindowProps& props);
            virtual void shutdown();

            GLFWwindow* m_window;

            struct WindowData {
                std::string title;
                unsigned int width, height;
                bool vSync;

                EventCallbackFn eventCallback;
            };

            WindowData m_data;
    };
}
#endif

#ifdef PLATFORM_IOS
#endif