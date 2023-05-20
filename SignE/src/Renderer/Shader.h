#ifndef SHADER_H
#define SHADER_H

#include "Ref.h"

#include <string>
#include <glm/glm.hpp>

namespace SignE::Core::Renderer
{

class Shader
{
public:
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void SetInt(const std::string& name, int value) = 0;
    virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
    virtual void SetFloat(const std::string& name, float value) = 0;
    virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
    virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
    virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
    virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

    static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
};
} // namespace SignE::Core::Renderer

#endif // !SHADER_H
