#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace SignE::Core::Application {

class Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window() { glfwTerminate(); }

    bool ShouldClose() const { return glfwWindowShouldClose(window); }
    void SwapBuffers() const { glfwSwapBuffers(window); }
    void PollEvents() const;

    void BeginImGuiFrame() const;
    void EndImGuiFrame() const;

    GLFWwindow* GetNativeWindow() const { return window; }
private:
    std::string title;
    int width;
    int height;

    GLFWwindow* window;
};

} // namespace SignE::Application

#endif // !WINDOW_H
