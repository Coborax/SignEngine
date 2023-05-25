#ifndef TEXTURE_H
#define TEXTURE_H

#include "Ref.h"

#include "Resources/Resources.h"

namespace SignE::Core::Renderer
{
    class Texture;
}

namespace SignE::Core {
using RenderTexture = Renderer::Texture;

class Texture : public Resource
{
public:
    Texture() = default;
    ~Texture() = default;

    void Load(const std::string& path) override;
    void Cleanup() override;

    Ref<RenderTexture> GetTexture() const { return texture; }
private:
    Ref<RenderTexture> texture;
};

}

#endif // !#ifndef TEXTURE_H
