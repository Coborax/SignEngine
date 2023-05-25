#include "OpenGLRenderer.h"
#include "Log.h"
#include "Renderer/VertexArray.h"
#include "Renderer/IndexBuffer.h"


#include <imgui.h>
#include <imgui_impl_opengl3.h>

namespace SignE::Core::Renderer
{

void OpenGLRenderer::Init()
{
    if (Renderer::GetAPI() == RenderAPI::None)
    {
        Log::LogError("No render api selected");
        throw std::runtime_error("No render api selected");
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEBUG_OUTPUT);

    ImGui_ImplOpenGL3_Init();
}

void OpenGLRenderer::SetClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void OpenGLRenderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::DrawIndexed(const Ref<VertexArray>& vertexArray)
{
    glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderer::DrawIndexedLines(const Ref<VertexArray>& vertexArray)
{
    glDrawElements(GL_LINES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderer::BeginImGuiFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
}

void OpenGLRenderer::EndImGuiFrame()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void OpenGLRenderer::SetViewport(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

} // namespace SignE::Core::Renderer
