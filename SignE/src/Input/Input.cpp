#include "Input.h"

#include "Application/Application.h"
#include "Application/Window.h"
#include "Log.h"
#include <string>

namespace SignE::Core::Input {

    float Input::lastX = 0.0f;
    float Input::lastY = 0.0f;
    float Input::xOffset = 0.0f;
    float Input::yOffset = 0.0f;
    bool Input::firstMouse = true;

    bool Input::IsKeyPressed(KeyCode keycode)
    {
        auto window = Application::Application::GetWindow()->GetNativeWindow();
        //TODO: Remove glfwGetKey and replace with a abstraction 
        auto state = glfwGetKey(window, static_cast<int32_t>(keycode));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    std::pair<float, float> Input::GetMouseDelta()
    {
        return std::make_pair(xOffset, yOffset);
    }

    bool Input::IsMouseButtonPressed(int button)
    {
        return glfwGetMouseButton(Application::Application::GetWindow()->GetNativeWindow(), button) == GLFW_PRESS;
    }

    bool Input::IsMouseButtonReleased(int button)
    {
        return glfwGetMouseButton(Application::Application::GetWindow()->GetNativeWindow(), button) == GLFW_RELEASE;
    }

    void Input::MouseCallback(double xpos, double ypos)
    {
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        xOffset = xpos - lastX;
        yOffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;
    }

    void Input::ResetMouseOffset()
    {
        xOffset = 0.0f;
        yOffset = 0.0f;
    }
}
