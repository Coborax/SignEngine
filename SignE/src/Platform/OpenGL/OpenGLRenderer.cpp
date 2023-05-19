#include "OpenGLRenderer.h"
#include "Log.h"
#include "Renderer/VertexArray.h"
#include "Renderer/IndexBuffer.h"

namespace SignE::Core::Renderer
{

void OpenGLRenderer::Init()
{
    if (Renderer::GetAPI() == RenderAPI::None)
    {
        Log::LogError("No render api selected");
        throw std::runtime_error("No render api selected");
    }
}

void OpenGLRenderer::SetClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void OpenGLRenderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::DrawIndexed(const Ref<VertexArray>& vertexArray)
{
    glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}
} // namespace SignE::Core::Renderer
