#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexBuffer.h"
namespace SignE::Core::Renderer
{
class VertexArray
{
public:
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
    virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

    virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
    virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

    static Ref<VertexArray> Create();
};
}

#endif // !#ifndef VERTEXARRAY_H

