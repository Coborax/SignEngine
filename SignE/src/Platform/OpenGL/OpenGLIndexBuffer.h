#ifndef OPENGLINDEXBUFFER_H
#define OPENGLINDEXBUFFER_H

#include "Renderer/IndexBuffer.h"

namespace SignE::Core::Renderer
{
class OpenGLIndexBuffer : public IndexBuffer
{
public:
    OpenGLIndexBuffer(const unsigned int* data, unsigned int count);
    ~OpenGLIndexBuffer();

    void Bind() const override;
    void Unbind() const override;

    unsigned int GetCount() const override
    {
        return count;
    }

private:
    unsigned int renderId;
    unsigned int count;
};
} // namespace SignE::Core::Renderer

#endif // !#ifndef OPENGLINDEXBUFFER_HDEBUG
