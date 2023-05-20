#include "OpenGLShader.h"

#include "Log.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

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

void OpenGLShader::SetInt(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(rendererID, name.c_str()), value);
}

void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
{
    glUniform1iv(glGetUniformLocation(rendererID, name.c_str()), count, values);
}

void OpenGLShader::SetFloat(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(rendererID, name.c_str()), value);
}

void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
{
    glUniform2f(glGetUniformLocation(rendererID, name.c_str()), value.x, value.y);
}

void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
{
    glUniform3f(glGetUniformLocation(rendererID, name.c_str()), value.x, value.y, value.z);
}

void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
{
    glUniform4f(glGetUniformLocation(rendererID, name.c_str()), value.x, value.y, value.z, value.w);
}

void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
{
    glUniformMatrix4fv(glGetUniformLocation(rendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}


} // namespace SignE::Core::Renderer
