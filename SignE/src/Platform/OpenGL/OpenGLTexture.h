#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include "Renderer/Texture.h"

#include <string>

namespace SignE::Core::Renderer
{

class OpenGLTexture : public Texture
{
public:
    OpenGLTexture(const std::string& path);
    ~OpenGLTexture();

    void Bind(unsigned int slot = 0) const override;
    void Unbind() const override;

    unsigned int GetWidth() const override
    {
        return width;
    }
    unsigned int GetHeight() const override
    {
        return height;
    }

private:
    unsigned int rendererID;

    std::string path;
    unsigned char* data;
    int width, height, channels;
};

} // namespace SignE::Core::Renderer
#endif // !#ifndef OPENGL_TEXTURE_H
