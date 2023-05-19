#include "OpenGLShader.h"

#include "Log.h"

#include <GL/glew.h>

namespace SignE::Core::Renderer
{

unsigned int OpenGLShader::CompileShader(const std::string& source, unsigned int type)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        // char* message = (char*) alloca(length * sizeof(char));
        // glGetShaderInfoLog(id, length, &length, message);
        Log::LogError("Failed to compile vertex shader!");
        // std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
    : Shader(vertexSrc, fragmentSrc)
{
    rendererID = glCreateProgram();

    unsigned int vertexShader = CompileShader(vertexSrc, GL_VERTEX_SHADER);
    unsigned int fragmentShader = CompileShader(fragmentSrc, GL_FRAGMENT_SHADER);

    glAttachShader(rendererID, vertexShader);
    glAttachShader(rendererID, fragmentShader);
    glLinkProgram(rendererID);
    glValidateProgram(rendererID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(rendererID);
}

void OpenGLShader::Bind() const
{
    glUseProgram(rendererID);
}

void OpenGLShader::Unbind() const
{
    glUseProgram(0);
}

} // namespace SignE::Core::Renderer
