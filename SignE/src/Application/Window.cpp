#include "Window.h"

#include "Log.h"
#include "Renderer/Renderer.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace SignE::Core::Application
{

Window::Window(const std::string& title, int width, int height) : title(title), width(width), height(height)
{
    glfwInit();

    if (Renderer::Renderer::GetAPI() == Renderer::RenderAPI::OpenGL)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    // TODO: Check if mac
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window)
    {
        Log::LogError("Failed to create GLFW window");
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glewInit();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    if (Renderer::Renderer::GetAPI() == Renderer::RenderAPI::OpenGL)
    {
        ImGui_ImplGlfw_InitForOpenGL(window, true);
    }
}

void Window::PollEvents() const
{
    glfwPollEvents();
}

void Window::BeginImGuiFrame() const
{
    Renderer::RenderCommand::BeginImGuiFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Window::EndImGuiFrame() const
{
    ImGui::Render();
    Renderer::RenderCommand::EndImGuiFrame();
}
} // namespace SignE::Core::Application
