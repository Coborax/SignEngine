#ifndef RENDERER_3D_H
#define RENDERER_3D_H

#include "Ref.h"

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace SignE::Core
{
    struct Vertex;
    class Model;
}

namespace SignE::Core::Renderer
{
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;
    class Shader;
    class Texture;

    class Renderer3D
    {
    public:
        static void Init();
        static void Shutdown();

        static void Begin(const glm::mat4& viewProjection, const glm::mat4& viewMatrix, const glm::vec3& cameraPosition);
        static void End();

        static void Submit(const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f), const glm::vec3& albedo = glm::vec3(1.0f, 1.0f, 1.0f), float metallic = 0.0f, float roughness = 0.5f, float ao = 1.0f);
        static void Submit(const Ref<Model>& model, const glm::mat4& transform = glm::mat4(1.0f), const glm::vec3& albedo = glm::vec3(1.0f, 1.0f, 1.0f), float metallic = 0.0f, float roughness = 0.5f, float ao = 1.0f);

        static void Submit(const Ref<VertexArray>& vertexArray, const glm::mat4& transform, const Ref<Texture>& albedo, const Ref<Texture>& metallic, const Ref<Texture>& roughness, const Ref<Texture>& ao);
        static void Submit(const Ref<Model>& model, const glm::mat4& transform, const Ref<Texture>& albedo, const Ref<Texture>& metallic, const Ref<Texture>& roughness, const Ref<Texture>& ao);

        static void DrawGrid();

        static void AddLight(const glm::vec3& position, const glm::vec3& color);
    private:
        static Ref<Shader> shader;
        static std::string vs;
        static std::string fs;
        
        static Ref<VertexArray> gridVertexArray;
        static Ref<VertexBuffer> gridVertexBuffer;
        static Ref<IndexBuffer> gridIndexBuffer;

        static std::vector<Vertex> gridVertices;
        static std::vector<unsigned int> gridIndices;

        static std::vector<glm::vec3> lightPositions;
        static std::vector<glm::vec3> lightColors;
    };
}

#endif // !#ifndef RENDERER_3D_H
