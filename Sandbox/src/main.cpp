#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <iostream>

#include "../../SignE/src/SignE.h"

#include "Log.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/VertexArray.h"
#include "Resources/Model.h"
#include "Renderer/Renderer3D.h"
#include "tiny_obj_loader.h"

namespace SignE::Sandbox::Application
{
using SignE::Core::Application::Application;
using SignE::Core::Application::ApplicationLayer;

class SandboxLayer : public ApplicationLayer
{
public:
    SandboxLayer() : ApplicationLayer()
    {}

    void OnInit() override
    {
        // models.push_back(Core::Resources::Instance().Load<Core::Model>("models/Cube.obj"));
        // models.push_back(Core::Resources::Instance().Load<Core::Model>("models/bunny.obj"));
        // models.push_back(Core::Resources::Instance().Load<Core::Model>("models/snickle.obj"));
        // models.push_back(Core::Resources::Instance().Load<Core::Model>("models/female.obj"));
        models.push_back(Core::Resources::Instance().Load<Core::Model>("models/keytruck/keytruck.obj"));
        textures.push_back(Core::Renderer::Texture::Create("models/keytruck/keytruck.png"));

        // models.push_back(Core::Resources::Instance().Load<Core::Model>("models/Sword/Sword.obj"));
        // textures.push_back(Core::Renderer::Texture::Create("models/Sword/Textures/Color.png"));

        models.push_back(Core::Resources::Instance().Load<Core::Model>("models/VikingRoom/viking_room.obj"));
        textures.push_back(Core::Renderer::Texture::Create("models/VikingRoom/viking_room.png"));
    }

    void OnUpdate(float deltaTime) override
    {
    }

    void OnDraw() override
    {
        glm::mat4 viewMatrix =
            glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat3 projectionMatrix = glm::perspective(glm::radians(45.0f),
                                                      (float) Core::Application::Application::GetWindow()->GetWidth() /
                                                          (float) Core::Application::Application::GetWindow()->GetHeight(),
                                                      0.1f, 100.0f);

        Core::Renderer::Renderer3D::Begin(viewMatrix, projectionMatrix);
        for (auto& model : models)
        {
            Core::Renderer::Renderer3D::Submit(model);
        }
        Core::Renderer::Renderer3D::End();
    }

    void OnShutdown() override
    {}

private:
    std::vector<Ref<Core::Model>> models;
    std::vector<Ref<Core::Renderer::Texture>> textures;
};

// class DebugLayer : public ImGuiLayer
// {
//
// };

class SandboxApplication : public Application
{
public:
    SandboxApplication() : Application("Sandbox")
    {
        Core::VFS::Instance().Mount("/Users/cobo/Dev/GlobalAssets/models", "models");
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
