#include "OpenGLTexture.h"
#include "FileSystem/VirtualFileSystem.h"

#include "Helpers/stb_image.h"

#include "Log.h"

#include <GL/glew.h>

namespace SignE::Core::Renderer
{
OpenGLTexture::OpenGLTexture(const std::string& path) : path(path)
{
    data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (!data)
    {
        Log::LogError("Failed to load image: " + path);
        throw std::runtime_error("Failed to load image: " + path);
    }

    GLenum internalFormat = 0, dataFormat = 0;
    if (channels == 4)
    {
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
    }
    else if (channels == 3)
    {
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
    }

    glGenTextures(1, &rendererID);
    glBindTexture(GL_TEXTURE_2D, rendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}


OpenGLTexture::~OpenGLTexture()
{
    glDeleteTextures(1, &rendererID);
}

void OpenGLTexture::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, rendererID);
}

void OpenGLTexture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace SignE::Core::Renderer
