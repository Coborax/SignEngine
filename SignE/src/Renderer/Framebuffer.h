#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "Ref.h"

namespace SignE::Core::Renderer
{

class Framebuffer
{
public:
    Framebuffer(unsigned int width, unsigned int height) {};
    virtual ~Framebuffer() = default;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void Resize(unsigned int width, unsigned int height) = 0;

    virtual unsigned int GetColorAttachmentRendererID() const = 0;

    static Ref<Framebuffer> Create(unsigned int width, unsigned int height);
};
} // namespace SignE::Core::Renderer

#endif // !#ifndef FRAMEBUFFER_H
