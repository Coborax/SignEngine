#include "OpenGLIndexBuffer.h"

#include <GL/glew.h>

namespace SignE::Core::Renderer
{
OpenGLIndexBuffer::OpenGLIndexBuffer(const unsigned int* data, unsigned int count) : IndexBuffer(data, count), count(count)
{
    glGenBuffers(1, &renderId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &renderId);
}

void OpenGLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderId);
}

void OpenGLIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
} // namespace SignE::Core::Renderer
