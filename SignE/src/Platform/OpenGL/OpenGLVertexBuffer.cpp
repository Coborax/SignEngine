#include "OpenGLVertexBuffer.h"

#include <GL/glew.h>

namespace SignE::Core::Renderer
{
OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, unsigned int size) : VertexBuffer(data, size)
{
    glGenBuffers(1, &renderId);
    glBindBuffer(GL_ARRAY_BUFFER, renderId);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &renderId);
}

void OpenGLVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, renderId);
}

void OpenGLVertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

} // namespace SignE::Core::Renderer
