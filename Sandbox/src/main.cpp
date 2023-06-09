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
#include "Scene/Entity.h"
#include "Scene/Scene.h"
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
        SetActiveScene(CreateRef<Core::Scene::Scene>());

        auto sphere = ActiveScene->CreateEntity("Sphere");
    }

private:
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
