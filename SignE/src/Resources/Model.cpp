#include "Model.h"
#include "FileSystem/VirtualFileSystem.h"
#include "Log.h"
#include "Renderer/VertexArray.h"

#include <glm/ext/scalar_constants.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <tiny_obj_loader.h>

namespace SignE::Core
{

void Model::Load()
{
    switch (type)
    {
        case None:
            LoadModel();
            break;
        case Cube:
        case Plane:
        case Sphere:
            LoadSphere();
            break;
    }
    vertexArray = Renderer::VertexArray::Create();

    vertexBuffer = Renderer::VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(Vertex));
    vertexBuffer->SetLayout({{Renderer::ShaderDataType::Float3, "vertexPosition"},
                             {Renderer::ShaderDataType::Float3, "vertexNormal"},
                             {Renderer::ShaderDataType::Float2, "vertexTexCoords"}});

    indexBuffer = Renderer::IndexBuffer::Create(indices.data(), indices.size());

    vertexArray->AddVertexBuffer(vertexBuffer);
    vertexArray->SetIndexBuffer(indexBuffer);
}

void Model::LoadSphere()
{
    auto radius = 1.0f;
    auto stackCount = 18;
    auto sectorCount = 36;

    auto x = 0.0f;
    auto y = 0.0f;
    auto z = 0.0f;

    auto sectorStep = 2 * glm::pi<float>() / sectorCount;
    auto stackStep = glm::pi<float>() / stackCount;
    auto sectorAngle = 0.0f;
    auto stackAngle = 0.0f;

    for (auto i = 0; i <= stackCount; ++i)
    {
        stackAngle = glm::half_pi<float>() - i * stackStep;
        auto xy = radius * glm::cos(stackAngle);
        z = radius * glm::sin(stackAngle);

        for (auto j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;

            x = xy * glm::cos(sectorAngle);
            y = xy * glm::sin(sectorAngle);

            auto nx = x / radius;
            auto ny = y / radius;
            auto nz = z / radius;

            auto s = (float)j / sectorCount;
            auto t = (float)i / stackCount;

            vertices.push_back({glm::vec3(x, y, z), glm::vec3(nx, ny, nz), glm::vec2(s, t)});
        }
    }

    auto k1 = 0;
    auto k2 = 0;

    for (auto i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);
        k2 = k1 + sectorCount + 1;

        for (auto j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stackCount - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}

void Model::LoadModel()
{
    auto absolutePath = VFS::Instance().GetAbsolutePath(GetPath());
    Log::LogInfo("Loading model: " + absolutePath);

    std::string error;
    std::string warning;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    tinyobj::LoadObj(&attrib, &shapes, &materials, &warning, &error, absolutePath.c_str());

    if (!error.empty())
    {
        Log::LogError("Model failed to load: " + error);
        return;
    }

    if (!warning.empty())
    {
        // TODO: Log warnings with Log::LogWarning
        Log::LogInfo("Model loaded with warnings: " + warning);
    }

    bool hasNormals = !attrib.normals.empty();
    bool hasTexCoords = !attrib.texcoords.empty();
    for (const auto& shape : shapes)
    {
        for (const auto& index : shape.mesh.indices)
        {
            auto position =
                glm::vec3(attrib.vertices[3 * index.vertex_index + 0], attrib.vertices[3 * index.vertex_index + 1],
                          attrib.vertices[3 * index.vertex_index + 2]);

            auto normal = glm::vec3(0.0f);
            if (hasNormals)
            {
                normal =
                    glm::vec3(attrib.normals[3 * index.normal_index + 0], attrib.normals[3 * index.normal_index + 1],
                              attrib.normals[3 * index.normal_index + 2]);
            }

            auto texcoords = glm::vec2(0.0f);
            if (hasTexCoords)
            {
                texcoords = glm::vec2(attrib.texcoords[2 * index.texcoord_index + 0],
                                      1.0f - attrib.texcoords[2 * index.texcoord_index + 1]);
            }

            vertices.push_back({position, normal, texcoords});
            indices.push_back(vertices.size() - 1);
        }
    }

    if (!hasNormals)
    {
        for (int j = 0; j < indices.size(); j += 3)
        {
            auto& v0 = vertices[indices[j + 0]];
            auto& v1 = vertices[indices[j + 1]];
            auto& v2 = vertices[indices[j + 2]];

            auto normal = glm::normalize(glm::cross(v1.position - v0.position, v2.position - v0.position));

            v0.normal = normal;
            v1.normal = normal;
            v2.normal = normal;
        }
    }
}

void Model::Cleanup()
{}

} // namespace SignE::Core
