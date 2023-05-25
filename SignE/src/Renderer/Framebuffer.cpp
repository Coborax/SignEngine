#include "Framebuffer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

#include "Log.h"
#include "Renderer/Renderer.h"

namespace SignE::Core::Renderer
{

Ref<Framebuffer> Framebuffer::Create(unsigned int width, unsigned int height)
{
    auto api = Renderer::Renderer::GetAPI();
    switch (api)
    {
        case RenderAPI::OpenGL:
            return static_cast<Ref<Framebuffer>>(CreateRef<OpenGLFramebuffer>(width, height));
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

} // namespace SignE::Core::Renderer
