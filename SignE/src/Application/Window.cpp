#include "Window.h"

#include "Log.h"

namespace SignE::Core::Application {

Window::Window(const std::string &title, int width, int height)
    : title(title), width(width), height(height) {

  // TODO: Check if render api is opengl and if mac for opengl forward
  // compatibility
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if (!window) {
    Log::LogError("Failed to create GLFW window");
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }

  glfwMakeContextCurrent(window);

  glewInit();
}

} // namespace SignE::Core::Application
