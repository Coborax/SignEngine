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

private:
    unsigned int rendererID;

    unsigned int CompileShader(const std::string& source, unsigned int type);
};
} // namespace SignE::Core::Renderer

#endif // !#ifndef OPENGLSHADER_H
