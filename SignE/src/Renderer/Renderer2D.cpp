//
// Created by Mikkel Mouridsen on 18/12/2022.
//

#include "Renderer2D.h"
#include "Log.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"

// TODO: Remove this
#include <GL/glew.h>

#include <iostream>

namespace SignE::Core::Renderer
{

// Rectangle vertices
float Renderer2D::vertices[] = {
    0.5f,  0.5f,  // top right
    0.5f,  -0.5f, // bottom right
    -0.5f, -0.5f, // bottom left
    -0.5f, 0.5f   // top left
};

unsigned int Renderer2D::indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

Ref<VertexBuffer> Renderer2D::vertexBuffer = nullptr;
Ref<IndexBuffer> Renderer2D::indexBuffer = nullptr;
Ref<VertexArray> Renderer2D::vertexArray = nullptr;
Ref<Shader> Renderer2D::shader = nullptr;

void Renderer2D::Init()
{
    Log::LogInfo("Initializing Renderer2D");

    vertexArray = VertexArray::Create();

    vertexBuffer = VertexBuffer::Create(&vertices, sizeof(vertices));
    vertexBuffer->SetLayout({
        {ShaderDataType::Float2, "position"},
    });

    indexBuffer = IndexBuffer::Create(indices, sizeof(indices));

    vertexArray->AddVertexBuffer(vertexBuffer);
    vertexArray->SetIndexBuffer(indexBuffer);

    std::string vs = R"(
        #version 330 core

        layout(location = 0) in vec4 position;

        void main() {
            gl_Position = position;
        }
    )";

    std::string fs = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        void main() {
            color = vec4(1.0, 0.0, 0.0, 1.0);
        }
    )";

    shader = Shader::Create(vs, fs);
}

void Renderer2D::BeginDraw()
{}

void Renderer2D::EndDraw()
{}

void Renderer2D::DrawRect(int posX, int posY, int width, int height)
{
    shader->Bind();
    vertexArray->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer2D::DrawRect(int posX, int posY, int width, int height, float r, float g, float b, float a)
{
    shader->Bind();
    vertexArray->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer2D::BeginImGui()
{}

void Renderer2D::EndImGui()
{}

void Renderer2D::CleanupImGui()
{}

void Renderer2D::InitRenderTexture()
{}

void Renderer2D::CleanupRenderTexture()
{}

void Renderer2D::BeginDrawRenderTexture()
{}

void Renderer2D::EndDrawRenderTexture()
{}

void Renderer2D::ImGuiDrawRenderTexture(int width, int height)
{}

void Renderer2D::DrawFPS()
{}

} // namespace SignE::Core::Renderer
