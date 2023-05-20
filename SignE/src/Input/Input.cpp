#include "Input.h"

#include "Application/Application.h"
#include "Application/Window.h"

namespace SignE::Core::Input {
    bool Input::IsKeyPressed(KeyCode keycode)
    {
        auto window = Application::Application::GetWindow()->GetNativeWindow();
        auto state = glfwGetKey(window, static_cast<int32_t>(keycode));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }
}
