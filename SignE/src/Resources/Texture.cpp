#include "Texture.h"

#include "Renderer/Texture.h"

namespace SignE::Core
{
    void Texture::Load(const std::string& path)
    {
        texture = RenderTexture::Create(path);
    }

    void Texture::Cleanup()
    {
        texture.reset();
    }
}
