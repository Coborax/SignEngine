#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

#include "Renderer/Shader.h"

namespace SignE::Core::Renderer
{
class OpenGLShader : public Shader
{
public:
    OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~OpenGLShader();

    void Bind() const override;
    void Unbind() const override;

    void SetInt(const std::string& name, int value) override;
    void SetIntArray(const std::string& name, int* values, uint32_t count) override;
    void SetBool(const std::string& name, bool value) override;
    void SetFloat(const std::string& name, float value) override;
    void SetFloat2(const std::string& name, const glm::vec2& value) override;
    void SetFloat3(const std::string& name, const glm::vec3& value) override;
    void SetFloat4(const std::string& name, const glm::vec4& value) override;
    void SetMat4(const std::string& name, const glm::mat4& value) override;

    void SetFloat3Array(const std::string& name, const glm::vec3* values, uint32_t count) override;

private:
    unsigned int rendererID;
    unsigned int CompileShader(const std::string& source, unsigned int type);
};
} // namespace SignE::Core::Renderer

#endif // !#ifndef OPENGLSHADER_H
