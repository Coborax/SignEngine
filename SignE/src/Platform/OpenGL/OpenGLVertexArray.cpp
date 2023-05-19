#include "OpenGLVertexArray.h"

#include <GL/glew.h>

namespace SignE::Core::Renderer
{

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
    switch (type)
    {
        case ShaderDataType::Float:
            return GL_FLOAT;
        case ShaderDataType::Float2:
            return GL_FLOAT;
        case ShaderDataType::Float3:
            return GL_FLOAT;
        case ShaderDataType::Float4:
            return GL_FLOAT;
        case ShaderDataType::Mat3:
            return GL_FLOAT;
        case ShaderDataType::Mat4:
            return GL_FLOAT;
        case ShaderDataType::Int:
            return GL_INT;
        case ShaderDataType::Int2:
            return GL_INT;
        case ShaderDataType::Int3:
            return GL_INT;
        case ShaderDataType::Int4:
            return GL_INT;
        case ShaderDataType::Bool:
            return GL_BOOL;
        case ShaderDataType::None:
            return 0;
    }
}

OpenGLVertexArray::OpenGLVertexArray()
{
    glGenVertexArrays(1, &renderId);
    glBindVertexArray(renderId);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &renderId);
}

void OpenGLVertexArray::Bind() const
{
    glBindVertexArray(renderId);
}

void OpenGLVertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
{
    glBindVertexArray(renderId);
    vertexBuffer->Bind();

    const auto& layout = vertexBuffer->GetLayout();
    for (const auto& element : layout)
    {
        glEnableVertexAttribArray(vertexBufferIndex);
        glVertexAttribPointer(vertexBufferIndex, element.GetComponentCount(),
                              ShaderDataTypeToOpenGLBaseType(element.type), element.normalized ? GL_TRUE : GL_FALSE,
                              layout.GetStride(), (const void*)element.offset);
        vertexBufferIndex++;
    }

    vertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
{
    glBindVertexArray(renderId);
    indexBuffer->Bind();

    this->indexBuffer = indexBuffer;
}
} // namespace SignE::Core::Renderer
