#ifndef OPENGLVERTEXARRAY_H
#define OPENGLVERTEXARRAY_H

#include "Renderer/VertexArray.h"
namespace SignE::Core::Renderer
{
class VertexArray;
class OpenGLVertexArray : public VertexArray
{
public:
    OpenGLVertexArray();
    ~OpenGLVertexArray();

    void Bind() const override;
    void Unbind() const override;

    void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
    void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

    const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override
    {
        return vertexBuffers;
    }

    const Ref<IndexBuffer>& GetIndexBuffer() const override
    {
        return indexBuffer;
    }

private:
    unsigned int renderId;
    unsigned int vertexBufferIndex = 0;
    std::vector<Ref<VertexBuffer>> vertexBuffers;
    Ref<IndexBuffer> indexBuffer;
};
} // namespace SignE::Core::Renderer

#endif // !DEBUG
