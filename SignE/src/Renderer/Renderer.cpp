#include "Renderer.h"
#include "Platform/OpenGL/OpenGLRenderer.h"

#include "Log.h"
#include "Ref.h"

namespace SignE::Core::Renderer
{

// RenderAPI is default to None, so that the user has to set it
RenderAPI Renderer::api = RenderAPI::None;

Unique<Renderer> Renderer::Create()
{
    switch (api)
    {
        case RenderAPI::OpenGL:
            return static_cast<Unique<Renderer>>(CreateUnique<OpenGLRenderer>());
        case RenderAPI::Vulkan:
            Log::LogError("Vulkan is not supported yet");
            throw std::runtime_error("Vulkan is not supported yet");
        case RenderAPI::DirectX:
            Log::LogError("DirectX is not supported yet");
            throw std::runtime_error("DirectX is not supported yet");
        case RenderAPI::Metal:
            Log::LogError("Metal is not supported yet");
            throw std::runtime_error("Metal is not supported yet");
        default:
            Log::LogError("No render api selected");
            throw std::runtime_error("No render api selected");
    }
}

Unique<Renderer> RenderCommand::renderer = nullptr;

void RenderCommand::Init()
{
    Renderer::Create()->Init();
}

void RenderCommand::SetClearColor(float r, float g, float b, float a)
{
    renderer->SetClearColor(r, g, b, a);
}

void RenderCommand::Clear()
{
    renderer->Clear();
}

void RenderCommand::DrawIndexed(const Ref<VertexArray>& vertexArray)
{
    renderer->DrawIndexed(vertexArray);
}

void RenderCommand::Create(RenderAPI api)
{
    Renderer::SetAPI(api);
    renderer = Renderer::Create();
}
} // namespace SignE::Core::Renderer
