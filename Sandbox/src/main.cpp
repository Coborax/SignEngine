#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <iostream>

#include "../../SignE/src/SignE.h"

#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "tiny_obj_loader.h"

namespace SignE::Sandbox::Application
{
using SignE::Core::Application::Application;
using SignE::Core::Application::ApplicationLayer;

class OrbitCamera
{
public:
    OrbitCamera(float radius, float initialYaw, float initialPitch, glm::vec3 orbitCenter, float fov, float aspectRatio,
                float nearPlane, float farPlane)
        : radius(radius)
        , yaw(initialYaw)
        , pitch(initialPitch)
        , morbitCenter(orbitCenter)
        , fov(fov)
        , aspectRadius(aspectRatio)
        , nearPlane(nearPlane)
        , farPlane(farPlane)
    {
        UpdateCameraVectors();
    }

    void Update(float deltaTime)
    {
        GLFWwindow* window = glfwGetCurrentContext();

        // Move the camera position based on key inputs
        if (Core::Input::Input::IsKeyPressed(Core::Input::KeyCode::W))
        {
            pitch += m_movementSpeed;
        }
        if (Core::Input::Input::IsKeyPressed(Core::Input::KeyCode::S))
        {
            pitch -= m_movementSpeed;
        }
        if (Core::Input::Input::IsKeyPressed(Core::Input::KeyCode::A))
        {
            yaw += m_movementSpeed;
        }
        if (Core::Input::Input::IsKeyPressed(Core::Input::KeyCode::D))
        {
            yaw -= m_movementSpeed;
        }

        UpdateCameraVectors();
    }

    glm::mat4 GetViewMatrix() const
    {
        return glm::lookAt(m_position, morbitCenter, m_up);
    }

    glm::mat4 GetProjectionMatrix() const
    {
        return glm::perspective(glm::radians(fov), aspectRadius, nearPlane, farPlane);
    }

private:
    float radius;
    float yaw;
    float pitch;
    glm::vec3 morbitCenter;

    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;

    float m_movementSpeed = 1.0f;  // Adjust the camera movement speed
    float m_rotationSpeed = 10.0f; // Adjust the camera rotation speed

    float fov;         // Field of view
    float aspectRadius; // Aspect ratio
    float nearPlane;   // Near clipping plane
    float farPlane;    // Far clipping plane

    void UpdateCameraVectors()
    {
        // Calculate the new position of the camera
        float radYaw = glm::radians(yaw);
        float radPitch = glm::radians(pitch);
        m_position.x = morbitCenter.x + radius * glm::cos(radYaw) * glm::cos(radPitch);
        m_position.y = morbitCenter.y + radius * glm::sin(radPitch);
        m_position.z = morbitCenter.z + radius * glm::sin(radYaw) * glm::cos(radPitch);

        // Update the camera's orientation
        m_front = glm::normalize(morbitCenter - m_position);
        m_right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), m_front));
        m_up = glm::normalize(glm::cross(m_front, m_right));
    }
};

static std::string vs = R"(
#version 330 core

layout(location = 0) in vec3 a_position;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(a_position, 1.0);
}
)";
static std::string fs = R"(
#version 330 core

out vec4 FragColor;

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);  // White light color
    vec3 objectColor = vec3(0.5, 0.5, 0.5);  // Gray object color

    FragColor = vec4(objectColor * lightColor, 1.0);
}
)";

class SandboxLayer : public ApplicationLayer
{
public:
    SandboxLayer() : ApplicationLayer(), camera(5.0f, 0.0f, 0.0f, glm::vec3(0.0f), 90.0f, 1.0f, 0.1f, 100.0f)
    {}

    void OnInit() override
    {
        vertexArray = Core::Renderer::VertexArray::Create();

        // tinyobj::LoadObj(&attrib, &shapes, &materials, nullptr, nullptr, "/Users/cobo/Dev/bunny.obj");
        //
        //
        // vertexBuffer = Core::Renderer::VertexBuffer::Create(&attrib.vertices[0], attrib.vertices.size() *
        // sizeof(float)); vertexBuffer->SetLayout({
        //     { Core::Renderer::ShaderDataType::Float3, "a_Position" },
        //     { Core::Renderer::ShaderDataType::Float3, "a_Normal" },
        //     { Core::Renderer::ShaderDataType::Float2, "a_TexCoord" }
        // });

        // indexBuffer = Core::Renderer::IndexBuffer::Create((unsigned int*)&shapes[0].mesh.indices[0],
        //                                                   shapes[0].mesh.indices.size());
        cubeVertices = {
            // Front face
            -0.5f, -0.5f, 0.5f, // Bottom left
            0.5f, -0.5f, 0.5f,  // Bottom right
            0.5f, 0.5f, 0.5f,   // Top right
            -0.5f, 0.5f, 0.5f,  // Top left

            // Back face
            -0.5f, -0.5f, -0.5f, // Bottom left
            0.5f, -0.5f, -0.5f,  // Bottom right
            0.5f, 0.5f, -0.5f,   // Top right
            -0.5f, 0.5f, -0.5f,  // Top left

            // Left face
            -0.5f, -0.5f, -0.5f, // Bottom left
            -0.5f, -0.5f, 0.5f,  // Bottom right
            -0.5f, 0.5f, 0.5f,   // Top right
            -0.5f, 0.5f, -0.5f,  // Top left

            // Right face
            0.5f, -0.5f, -0.5f, // Bottom left
            0.5f, -0.5f, 0.5f,  // Bottom right
            0.5f, 0.5f, 0.5f,   // Top right
            0.5f, 0.5f, -0.5f,  // Top left

            // Top face
            -0.5f, 0.5f, 0.5f,  // Bottom left
            0.5f, 0.5f, 0.5f,   // Bottom right
            0.5f, 0.5f, -0.5f,  // Top right
            -0.5f, 0.5f, -0.5f, // Top left

            // Bottom face
            -0.5f, -0.5f, 0.5f, // Bottom left
            0.5f, -0.5f, 0.5f,  // Bottom right
            0.5f, -0.5f, -0.5f, // Top right
            -0.5f, -0.5f, -0.5f // Top left
        };

        cubeIndices = {// Front face
                       0, 1, 2, 2, 3, 0,

                       // Back face
                       4, 5, 6, 6, 7, 4,

                       // Left face
                       8, 9, 10, 10, 11, 8,

                       // Right face
                       12, 13, 14, 14, 15, 12,

                       // Top face
                       16, 17, 18, 18, 19, 16,

                       // Bottom face
                       20, 21, 22, 22, 23, 20};

        vertexBuffer = Core::Renderer::VertexBuffer::Create(&cubeVertices[0], cubeVertices.size() * sizeof(float));
        vertexBuffer->SetLayout({
            {Core::Renderer::ShaderDataType::Float3, "a_Position"},
        });

        indexBuffer = Core::Renderer::IndexBuffer::Create(&cubeIndices[0], cubeIndices.size());

        vertexArray->AddVertexBuffer(vertexBuffer);
        vertexArray->SetIndexBuffer(indexBuffer);

        shader = Core::Renderer::Shader::Create(vs, fs);
    }

    void OnUpdate(float deltaTime) override
    {
        camera.Update(deltaTime);
    }

    void OnDraw() override
    {
        vertexArray->Bind();

        shader->Bind();
        shader->SetMat4("modelMatrix", glm::mat4(1.0f));
        shader->SetMat4("viewMatrix", camera.GetViewMatrix());
        shader->SetMat4("projectionMatrix", camera.GetProjectionMatrix());

        Core::Renderer::RenderCommand::DrawIndexed(vertexArray);
    }

    void OnShutdown() override
    {}

private:
    OrbitCamera camera;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::vector<float> cubeVertices;
    std::vector<unsigned int> cubeIndices;

    Ref<Core::Renderer::VertexArray> vertexArray;
    Ref<Core::Renderer::VertexBuffer> vertexBuffer;
    Ref<Core::Renderer::IndexBuffer> indexBuffer;

    Ref<Core::Renderer::Shader> shader;
};

class SandboxApplication : public Application
{
public:
    SandboxApplication() : Application("Sandbox")
    {
        PushLayer(&sandboxLayer);
    }

private:
    SandboxLayer sandboxLayer;
};

} // namespace SignE::Sandbox::Application

int main()
{
    std::unique_ptr<SignE::Core::Application::Application> app =
        std::make_unique<SignE::Sandbox::Application::SandboxApplication>();
    app->Run();
}
