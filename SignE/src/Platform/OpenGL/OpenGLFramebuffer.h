#ifndef OPENGLFRAMEBUFFER_H
#define OPENGLFRAMEBUFFER_H

#include "Renderer/Framebuffer.h"

namespace SignE::Core::Renderer
{

class OpenGLFramebuffer : public Framebuffer
{
public:
    OpenGLFramebuffer(unsigned int width, unsigned int height);
    ~OpenGLFramebuffer();

    void Bind() override;
    void Unbind() override;

    void Resize(unsigned int width, unsigned int height) override;

    unsigned int GetColorAttachmentRendererID() const override
    {
        return colorAttachment;
    }

private:
    unsigned int rendererId = 0;
    bool initialized = false;

    unsigned int colorAttachment;
    unsigned int depthAttachment;

    unsigned int width;
    unsigned int height;

    void CreateFramebuffer();
};

} // namespace SignE::Core::Renderer

#endif // !#ifndef FRAMEBUFFER_H
