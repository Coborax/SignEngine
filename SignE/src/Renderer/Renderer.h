#ifndef RENDERER_H
#define RENDERER_H

#include "../Ref.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace SignE::Core::Renderer
{
class VertexArray;

enum RenderAPI
{
    None = 0,
    OpenGL = 1,
    Vulkan = 2,
    DirectX = 3,
    Metal = 4
};

class Renderer
{
public:
    virtual ~Renderer() = default;

    virtual void Init() = 0;
    virtual void SetClearColor(float r, float g, float b, float a) = 0;
    virtual void Clear() = 0;

    virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;
    virtual void DrawIndexedLines(const Ref<VertexArray>& vertexArray) = 0;

    virtual void BeginImGuiFrame() = 0;
    virtual void EndImGuiFrame() = 0;

    virtual void SetViewport(int x, int y, int width, int height) = 0;

    static void SetAPI(RenderAPI api)
    {
        Renderer::api = api;
    }
    static RenderAPI GetAPI()
    {
        return api;
    }

    static Unique<Renderer> Create();

private:
    static RenderAPI api;
    Unique<Renderer> renderer;
};

class RenderCommand
{
public:
    static void Init();
    static void SetClearColor(float r, float g, float b, float a);
    static void Clear();

    static void DrawIndexed(const Ref<VertexArray>& vertexArray);
    static void DrawIndexedLines(const Ref<VertexArray>& vertexArray);

    static void Create(RenderAPI api);

    static void BeginImGuiFrame();
    static void EndImGuiFrame();

    static void SetViewport(int x, int y, int width, int height);

private:
    static Unique<Renderer> renderer;
};

} // namespace SignE::Core::Renderer

#endif // DEBUG
