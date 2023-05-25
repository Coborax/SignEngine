#include "OpenGLFramebuffer.h"
#include "Log.h"

#include <GL/glew.h>

namespace SignE::Core::Renderer
{
OpenGLFramebuffer::OpenGLFramebuffer(unsigned int width, unsigned int height) : Framebuffer(width, height), width(width), height(height)
{
    CreateFramebuffer();
}

OpenGLFramebuffer::~OpenGLFramebuffer()
{
    glDeleteFramebuffers(1, &rendererId);
    glDeleteTextures(1, &colorAttachment);
    glDeleteRenderbuffers(1, &depthAttachment);
}

void OpenGLFramebuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, rendererId);
    glViewport(0, 0, width, height);
}

void OpenGLFramebuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFramebuffer::Resize(unsigned int width, unsigned int height)
{
    if (this->width == width && this->height == height)
        return;

    this->width = width;
    this->height = height;

    CreateFramebuffer();
}

void OpenGLFramebuffer::CreateFramebuffer()
{
    if (initialized)
    {
        glDeleteFramebuffers(1, &rendererId);
        glDeleteTextures(1, &colorAttachment);
        glDeleteRenderbuffers(1, &depthAttachment);
    }

    glGenFramebuffers(1, &rendererId);
    glBindFramebuffer(GL_FRAMEBUFFER, rendererId);

    // Create a color attachment texture
    glGenTextures(1, &colorAttachment);
    glBindTexture(GL_TEXTURE_2D, colorAttachment);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Create a renderbuffer object for depth and stencil attachment
    glGenRenderbuffers(1, &depthAttachment);
    glBindRenderbuffer(GL_RENDERBUFFER, depthAttachment);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

    // Bind both to framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachment, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthAttachment);
}

} // namespace SignE::Core::Renderer
