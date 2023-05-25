#include "Resources/Model.h"
#include <vector>
#ifndef RENDERER_3D_H

#include "Ref.h"

#include <glm/glm.hpp>
#include <string>

namespace SignE::Core
{
    class Model;
}

namespace SignE::Core::Renderer
{
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;
    class Shader;

    class Renderer3D
    {
    public:
        static void Init();
        static void Shutdown();

        static void Begin(const glm::mat4& viewProjection, const glm::mat4& viewMatrix);
        static void End();

        static void Submit(const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
        static void Submit(const Ref<Model>& model, const glm::mat4& transform = glm::mat4(1.0f));

        static void DrawGrid();
    private:
        static Ref<Shader> shader;
        static std::string vs;
        static std::string fs;
        
        static Ref<VertexArray> gridVertexArray;
        static Ref<VertexBuffer> gridVertexBuffer;
        static Ref<IndexBuffer> gridIndexBuffer;

        static std::vector<Vertex> gridVertices;
        static std::vector<unsigned int> gridIndices;
    };
}

#endif // !#ifndef RENDERER_3D_H
