#include "Renderer.h"
#include "Renderer3D.h"
#include "Shader.h"
#include "Resources/Model.h"

#include "Renderer/VertexArray.h"

namespace SignE::Core::Renderer
{
std::string Renderer3D::vs = R"(
#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexCoords;

out vec3 fragPosition;
out vec3 fragNormal;
out vec2 fragTexCoords;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0);
    fragPosition = vec3(modelMatrix * vec4(vertexPosition, 1.0));
    fragNormal = mat3(transpose(inverse(modelMatrix))) * vertexNormal;
    fragTexCoords = vertexTexCoords;
}
)";

std::string Renderer3D::fs = R"(
#version 330 core

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoords;

out vec4 fragColor;

uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform float ambientStrength;
uniform float diffuseStrength;
uniform float specularStrength;
uniform float shininess;

uniform sampler2D objectTexture;

void main()
{
    // Ambient lighting
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse lighting
    vec3 norm = normalize(fragNormal);
    float diffuseFactor = max(dot(norm, -lightDirection), 0.0);
    vec3 diffuse = diffuseFactor * lightColor;

    // Specular reflection
    vec3 viewDir = normalize(-fragPosition);
    vec3 reflectDir = reflect(-lightDirection, norm);
    float specularFactor = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * specularFactor * lightColor;

    // Final color calculation
    vec3 result = (ambient + diffuse + specular) * texture(objectTexture, fragTexCoords).rgb * objectColor.rgb;

    // fragColor = vec4(result, 1.0);
    fragColor = texture(objectTexture, fragTexCoords); 
}
)";

Ref<Shader> Renderer3D::shader = nullptr;

Ref<VertexArray> Renderer3D::gridVertexArray = nullptr;
Ref<VertexBuffer> Renderer3D::gridVertexBuffer = nullptr;
Ref<IndexBuffer> Renderer3D::gridIndexBuffer = nullptr;

std::vector<Vertex> Renderer3D::gridVertices;
std::vector<unsigned int> Renderer3D::gridIndices;

void Renderer3D::Init()
{
    shader = Shader::Create(vs, fs);
    shader->SetFloat3("lightDirection", glm::normalize(glm::vec3(-0.5f, -0.5f, -1.0f)));
    shader->SetFloat3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    shader->SetFloat3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));
    shader->SetFloat("ambientStrength", 0.2f);
    shader->SetFloat("diffuseStrength", 0.8f);
    shader->SetFloat("specularStrength", 0.5f);
    shader->SetFloat("shininess", 32.0f);
}

void Renderer3D::Shutdown()
{}

void Renderer3D::Begin(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    shader->Bind();
    shader->SetMat4("viewMatrix", viewMatrix);
    shader->SetMat4("projectionMatrix", projectionMatrix);
}

void Renderer3D::End()
{
    shader->Unbind();
}

void Renderer3D::Submit(const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
{
    shader->SetMat4("modelMatrix", transform);
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}

void Renderer3D::Submit(const Ref<Model>& model, const glm::mat4& transform)
{
    Submit(model->GetVertexArray(), transform);
}

void Renderer3D::DrawGrid()
{
    if (!gridVertexArray) {

        int size = 100;

        // Generate grid plane along x and z axis
        for (int i = -size; i <= size; i++) {
            gridVertices.push_back({ glm::vec3(i, 0.0f, -size), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f) });
            gridVertices.push_back({ glm::vec3(i, 0.0f, size), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f) });
            gridVertices.push_back({ glm::vec3(-size, 0.0f, i), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f) });
            gridVertices.push_back({ glm::vec3(size, 0.0f, i), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f) });
        }

        for (int i = 0; i < gridVertices.size(); i++) {
            gridIndices.push_back(i);
        }
        

        gridVertexArray = VertexArray::Create();
        gridVertexBuffer = VertexBuffer::Create(gridVertices.data(), gridVertices.size() * sizeof(Vertex));
        gridVertexBuffer->SetLayout({
            { ShaderDataType::Float3, "vertexPosition" },
            { ShaderDataType::Float3, "vertexNormal" },
            { ShaderDataType::Float2, "vertexTexCoords" }
        });
        gridVertexArray->AddVertexBuffer(gridVertexBuffer);

        gridIndexBuffer = IndexBuffer::Create(gridIndices.data(), gridIndices.size());
        gridVertexArray->SetIndexBuffer(gridIndexBuffer);
    }

    // shader->SetFloat3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));
    shader->SetMat4("modelMatrix", glm::mat4(1.0f));
    gridVertexArray->Bind();
    RenderCommand::DrawIndexedLines(gridVertexArray);
}

} // namespace SignE::Core::Renderer
