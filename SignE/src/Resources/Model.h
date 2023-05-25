#ifndef MODEL_H
#define MODEL_H

#include "Resources/Resources.h"

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

namespace SignE::Core
{

namespace Renderer
{
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;
} // namespace Renderer

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

// struct Mesh
// {
//     std::vector<Vertex> vertices;
//     std::vector<unsigned int> indices;
// };

class Model : public Resource
{
public:
    Model() = default;
    ~Model() = default;

    void Load(const std::string& path) override;
    void Cleanup() override;

    Ref<Renderer::VertexArray> GetVertexArray() const { return vertexArray; }

private:
    // std::vector<Mesh> meshes;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Ref<Renderer::VertexArray> vertexArray;
    Ref<Renderer::VertexBuffer> vertexBuffer;
    Ref<Renderer::IndexBuffer> indexBuffer;
};

} // namespace SignE::Core

#endif // !#ifndef MODEL_H
