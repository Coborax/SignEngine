#include "Renderer3D.h"
#include "Log.h"
#include "Renderer.h"
#include "Renderer/Texture.h"
#include "Shader.h"
#include "Resources/Model.h"

#include "Renderer/VertexArray.h"

#include <vector>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace SignE::Core::Renderer
{
std::string Renderer3D::vs = R"(
#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexCoords;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 TexCoords;
out vec3 WorldPos;
out vec3 Normal;

void main()
{
    TexCoords = vertexTexCoords;
    WorldPos = vec3(modelMatrix * vec4(vertexPosition, 1.0));
    Normal = vertexNormal;

    gl_Position = projectionMatrix * viewMatrix * vec4(WorldPos, 1.0);
}
)";

std::string Renderer3D::fs = R"(
#version 330 core

out vec4 FragColor;
in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;

// material parameters
uniform vec3  albedoVal;
uniform float metallicVal;
uniform float roughnessVal;
uniform float aoVal;

uniform bool useTextures;
uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;

// lights
uniform vec3 lightPositions[4];
uniform vec3 lightColors[4];

uniform vec3 camPos;

const float PI = 3.14159265359;
  
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}  

vec3 getNormalFromMap()
{
    vec3 tangentNormal = texture(normalMap, TexCoords).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(WorldPos);
    vec3 Q2  = dFdy(WorldPos);
    vec2 st1 = dFdx(TexCoords);
    vec2 st2 = dFdy(TexCoords);

    vec3 N   = normalize(Normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

void main()
{
    vec3 albedo = vec3(0.0); 
    float metallic = 0.0;
    float roughness = 0.0;
    float ao = 0.0;
    vec3 normal = vec3(0.0);

    //TODO: Add normal mapping
    if(useTextures)
    {
        albedo    = pow(texture(albedoMap, TexCoords).rgb, vec3(2.2));
        metallic  = texture(metallicMap, TexCoords).r;
        roughness = texture(roughnessMap, TexCoords).r;
        ao        = texture(aoMap, TexCoords).r;
        normal    = getNormalFromMap();
    }
    else
    {
        albedo    = albedoVal;
        metallic  = metallicVal;
        roughness = roughnessVal;
        ao        = aoVal;
        normal    = normalize(Normal);
    }

    vec3 N = normal;
    vec3 V = normalize(camPos - WorldPos);

    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

    // reflectance equation
    vec3 Lo = vec3(0.0);
    for(int i = 0; i < 4; ++i) 
    {
        // calculate per-light radiance
        vec3 L = normalize(lightPositions[i] - WorldPos);
        vec3 H = normalize(V + L);
        float distance    = length(lightPositions[i] - WorldPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance     = lightColors[i] * attenuation;        
        
        // cook-torrance brdf
        float NDF = DistributionGGX(N, H, roughness);        
        float G   = GeometrySmith(N, V, L, roughness);      
        vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);       
        
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;	  
        
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
        vec3 specular     = numerator / denominator;  
            
        // add to outgoing radiance Lo
        float NdotL = max(dot(N, L), 0.0);                
        Lo += (kD * albedo / PI + specular) * radiance * NdotL; 
    }   
  
    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color = ambient + Lo;
	
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));  
   
    FragColor = vec4(color, 1.0);
}
)";

Ref<Shader> Renderer3D::shader = nullptr;

Ref<VertexArray> Renderer3D::gridVertexArray = nullptr;
Ref<VertexBuffer> Renderer3D::gridVertexBuffer = nullptr;
Ref<IndexBuffer> Renderer3D::gridIndexBuffer = nullptr;

std::vector<Vertex> Renderer3D::gridVertices;
std::vector<unsigned int> Renderer3D::gridIndices;

std::vector<glm::vec3> Renderer3D::lightPositions = {};
std::vector<glm::vec3> Renderer3D::lightColors = {};

void Renderer3D::Init()
{
    shader = Shader::Create(vs, fs);
}

void Renderer3D::Shutdown()
{}

void Renderer3D::Begin(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& cameraPosition)
{
    shader->Bind();
    shader->SetMat4("viewMatrix", viewMatrix);
    shader->SetMat4("projectionMatrix", projectionMatrix);
    shader->SetFloat3("camPos", cameraPosition);

    // Lights
    for (int i = lightPositions.size(); i < 4; i++)
    {
        lightPositions.push_back(glm::vec3(0.0f));
        lightColors.push_back(glm::vec3(0.0f));
    }

    if (lightPositions.size() > 4)
    {
        lightPositions.resize(4);
        lightColors.resize(4);
    }

    shader->SetFloat3Array("lightPositions", lightPositions.data(), 4);
    shader->SetFloat3Array("lightColors", lightColors.data(), 4);
}

void Renderer3D::End()
{
    lightPositions.clear();
    lightColors.clear();

    shader->Unbind();
}

void Renderer3D::Submit(const Ref<VertexArray>& vertexArray, const glm::mat4& transform, const glm::vec3& albedo,
                        float metallic, float roughness, float ao)
{
    shader->SetMat4("modelMatrix", transform);

    shader->SetBool("useTextures", false);
    shader->SetFloat3("albedoVal", albedo);
    shader->SetFloat("metallicVal", metallic);
    shader->SetFloat("roughnessVal", roughness);
    shader->SetFloat("aoVal", ao);

    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}

void Renderer3D::Submit(const Ref<Model>& model, const glm::mat4& transform, const glm::vec3& albedo, float metallic,
                        float roughness, float ao)
{
    Submit(model->GetVertexArray(), transform, albedo, metallic, roughness, ao);
}

void Renderer3D::Submit(const Ref<VertexArray>& vertexArray, const glm::mat4& transform, const Ref<Texture>& albedo, const Ref<Texture>& metallic, const Ref<Texture>& roughness, const Ref<Texture>& ao)
{
    shader->SetMat4("modelMatrix", transform);

    shader->SetBool("useTextures", true);
    shader->SetInt("albedoMap", 0);
    shader->SetInt("metallicMap", 1);
    shader->SetInt("roughnessMap", 2);
    shader->SetInt("aoMap", 3);

    albedo->Bind(0);
    metallic->Bind(1);
    roughness->Bind(2);
    ao->Bind(3);

    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}

void Renderer3D::Submit(const Ref<Model>& model, const glm::mat4& transform, const Ref<Texture>& albedo, const Ref<Texture>& metallic, const Ref<Texture>& roughness, const Ref<Texture>& ao)
{
    Submit(model->GetVertexArray(), transform, albedo, metallic, roughness, ao);
}

void Renderer3D::DrawGrid()
{
    if (!gridVertexArray)
    {
        int size = 100;

        // Generate grid plane along x and z axis
        for (int i = -size; i <= size; i++)
        {
            gridVertices.push_back({glm::vec3(i, 0.0f, -size), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f)});
            gridVertices.push_back({glm::vec3(i, 0.0f, size), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f)});
            gridVertices.push_back({glm::vec3(-size, 0.0f, i), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f)});
            gridVertices.push_back({glm::vec3(size, 0.0f, i), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f)});
        }

        for (int i = 0; i < gridVertices.size(); i++)
        {
            gridIndices.push_back(i);
        }

        gridVertexArray = VertexArray::Create();
        gridVertexBuffer = VertexBuffer::Create(gridVertices.data(), gridVertices.size() * sizeof(Vertex));
        gridVertexBuffer->SetLayout({{ShaderDataType::Float3, "vertexPosition"},
                                     {ShaderDataType::Float3, "vertexNormal"},
                                     {ShaderDataType::Float2, "vertexTexCoords"}});
        gridVertexArray->AddVertexBuffer(gridVertexBuffer);

        gridIndexBuffer = IndexBuffer::Create(gridIndices.data(), gridIndices.size());
        gridVertexArray->SetIndexBuffer(gridIndexBuffer);
    }

    shader->SetBool("useTextures", false);
    shader->SetFloat3("albedoVal", glm::vec3(0.0f));
    shader->SetFloat("metallicVal", 0.0f);
    shader->SetFloat("roughnessVal", 0.0f);
    shader->SetFloat("aoVal", 1.0f);

    shader->SetMat4("modelMatrix", glm::mat4(1.0f));
    gridVertexArray->Bind();
    RenderCommand::DrawIndexedLines(gridVertexArray);
}

void Renderer3D::AddLight(const glm::vec3& position, const glm::vec3& color)
{
    lightPositions.push_back(position);
    lightColors.push_back(color);
}

} // namespace SignE::Core::Renderer
