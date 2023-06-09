#ifndef TEXTURE_H
#define TEXTURE_H

#include "Ref.h"

#include "Resources/Resources.h"

namespace SignE::Core::Renderer
{
class Texture;
}

namespace SignE::Core
{

class TextureAsset : public Asset
{
public:
    TextureAsset(const std::string path) : Asset(path){};
    ~TextureAsset() = default;

    void Load() override;
    void Cleanup() override;

    Ref<Renderer::Texture> GetTexture() const
    {
        return texture;
    }

private:
    Ref<Renderer::Texture> texture;
};

} // namespace SignE::Core

#endif // !#ifndef TEXTURE_H
