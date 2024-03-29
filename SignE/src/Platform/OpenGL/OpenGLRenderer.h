#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "Renderer/Renderer.h"

namespace SignE::Core::Renderer {

class OpenGLRenderer : public Renderer {
public:
    void Init() override;
    void SetClearColor(float r, float g, float b, float a) override;
    void Clear() override;

    void DrawIndexed(const Ref<VertexArray> &vertexArray) override;
    void DrawIndexedLines(const Ref<VertexArray> &vertexArray) override;

    void BeginImGuiFrame() override;
    void EndImGuiFrame() override;

    void SetViewport(int x, int y, int width, int height) override;
};

} // namespace SignE::Core::Renderer

#endif // !#ifndef OPENGLRENDERER_H
