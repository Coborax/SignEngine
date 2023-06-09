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
//
enum PrimitiveType
{
    None,
    Cube,
    Plane,
    Sphere
};

class Model : public Asset
{
public:
    Model(const std::string path) : type(PrimitiveType::None), Asset(path){};
    Model(PrimitiveType type) : type(type), Asset("Primitive"){};
    ~Model() = default;

    void Load() override;
    void Cleanup() override;

    Ref<Renderer::VertexArray> GetVertexArray() const
    {
        return vertexArray;
    }

private:
    PrimitiveType type;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Ref<Renderer::VertexArray> vertexArray;
    Ref<Renderer::VertexBuffer> vertexBuffer;
    Ref<Renderer::IndexBuffer> indexBuffer;

    void LoadSphere();
    void LoadModel();
};

} // namespace SignE::Core

#endif // !#ifndef MODEL_H
