#ifndef RENDERTEXTURE_H
#define RENDERTEXTURE_H

#include "Ref.h"

#include <string>

namespace SignE::Core::Renderer
{

class Texture
{
public:
    virtual ~Texture() = default;

    virtual void Bind(unsigned int slot = 0) const = 0;
    virtual void Unbind() const = 0;

    virtual unsigned int GetWidth() const = 0;
    virtual unsigned int GetHeight() const = 0;

    static Ref<Texture> Create(const std::string& path);
};

} // namespace SignE::Core::Renderer

#endif // !#ifndef TEXTURE_H
