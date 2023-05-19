#ifndef SHADER_H
#define SHADER_H

#include "Ref.h"
#include <string>

namespace SignE::Core::Renderer
{

class Shader
{
public:
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
};
} // namespace SignE::Core::Renderer

#endif // !SHADER_H
