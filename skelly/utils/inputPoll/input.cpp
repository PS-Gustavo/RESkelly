#include <input.h>

namespace skelly {

    Input* Input::_s_instance = new PlatInput();

    bool PlatInput::m_isKeyPressedImpl(int keycode) {
        auto window = static_cast<GLFWwindow*>(Application::getApplication().getWindow().getNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return ((state == GLFW_PRESS) || (state == GLFW_REPEAT));
    }

    bool PlatInput::m_isMouseButtonPressedImpl(int button) {
        auto window = static_cast<GLFWwindow*>(Application::getApplication().getWindow().getNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return (state == GLFW_PRESS);
    }

    std::pair<float, float> PlatInput::m_getMouseCoordImpl() {
        auto window = static_cast<GLFWwindow*>(Application::getApplication().getWindow().getNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        return std::make_pair((float)xPos, (float)yPos);
    }

    float PlatInput::m_getMouseXImpl() {
        auto[x, y] = m_getMouseCoordImpl();
        return x;
    }

    float PlatInput::m_getMouseYImpl() {
        auto[x, y] = m_getMouseCoordImpl();
        return y;
    }

    

}