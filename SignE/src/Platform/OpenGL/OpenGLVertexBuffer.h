#ifndef OPENGLVERTEXBUFFER_H
#define OPENGLVERTEXBUFFER_H

#include "Renderer/VertexBuffer.h"

namespace SignE::Core::Renderer
{
class OpenGLVertexBuffer : public VertexBuffer
{
public:
    OpenGLVertexBuffer(const void* data, unsigned int size);
    ~OpenGLVertexBuffer();

    void Bind() const override;
    void Unbind() const override;

    const BufferLayout& GetLayout() const override { return layout; }
    void SetLayout(const BufferLayout& layout) override { this->layout = layout; }
private:
    unsigned int renderId;
    BufferLayout layout;
};
} // namespace SignE::Core::Renderer

#endif // !#ifndef OPENGLVERTEXBUFFER_H
