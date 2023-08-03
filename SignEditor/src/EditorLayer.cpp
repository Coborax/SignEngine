//
// Created by Mikkel Mouridsen on 19/12/2022.
//

#include "EditorLayer.h"

#include "Application/Application.h"
#include "Application/Window.h"
#include "Input/Input.h"
#include "Ref.h"
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"
#include "Resources/Model.h"
#include "Resources/Resources.h"
#include "Resources/Texture.h"
#include "Scene/Entity.h"
#include "Scene/Components.h"
#include "Scene/Scene.h"
#include "Scripting/LuaScriptEngine.h"
#include "Scene/SceneSerializer.h"
#include "Renderer/Framebuffer.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <imgui.h>
#include <ImGuizmo.h>
#include <memory>

namespace SignE::Editor::Application
{
using SignE::Core::Renderer::Renderer2D;
using SignE::Core::Scene::SceneSerializer;
using SignE::Core::Scene::Components::LuaScript;
using SignE::Core::Scene::Components::MeshRenderer;
using SignE::Core::Scene::Components::Position;
using SignE::Core::Scene::Components::Rect;
using SignE::Core::Scene::Components::RectangleRenderer;
using SignE::Core::Scene::Components::Tag;
using SignE::Core::Scene::Components::Transform;

void EditorLayer::OnInit()
{
    ImGuiLayer::OnInit();
    Renderer2D::InitRenderTexture();

    Core::Log::SetupInMemoryLog();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    editorScene = CreateRef<Scene>();
    SetActiveScene(editorScene);

    // Create default viewport
    EditorViewport viewport;
    viewport.framebuffer = Core::Renderer::Framebuffer::Create(1280, 720);
    viewport.camera = CreateRef<Core::Scene::PerspectiveCamera>();

    viewports.push_back(viewport);
}

void EditorLayer::OnDraw()
{
    DrawScene();
    DrawUI();
}

void EditorLayer::OnShutdown()
{
    ImGuiLayer::OnShutdown();
    Renderer2D::CleanupRenderTexture();
}

void EditorLayer::DrawGrid()
{}

void EditorLayer::DrawUI()
{
    EditorLayer::BeginImGui();

    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Scene"))
            {
                editorScene = CreateRef<Scene>();
                SetActiveScene(editorScene);
            }
            if (ImGui::MenuItem("Open Scene"))
            {
                editorScene = CreateRef<Scene>();
                SetActiveScene(editorScene);
                SceneSerializer serializer(editorScene);

                auto path = "scenes/sandbox.yaml";
                serializer.Serialize(path);
            }
            if (ImGui::MenuItem("Save Scene"))
            {
                SceneSerializer serializer(editorScene);

                auto path = "scenes/sandbox.yaml";
                serializer.Deserialize(path);
            }
            ImGui::Separator();
            if (ImGui::MenuItem("New Project"))
            {}
            if (ImGui::MenuItem("Open Project"))
            {}
            ImGui::Separator();
            if (ImGui::MenuItem("Exit"))
            {
                Core::Log::LogInfo("Exiting Editor");
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Tools"))
        {
            if (ImGui::MenuItem("Add PBR Example Spheres and Lights"))
            {
                for (int i = 0; i < 5; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        auto entity = editorScene->CreateEntity("Sphere" + std::to_string(i) + std::to_string(j));
                        auto pos = glm::vec3(i * 2.0f, j * 2.0f, 0.0f);
                        auto albedo = glm::vec3(1.0f, 0.0f, 0.0f);
                        auto metallic = (float)i / 5.0f;
                        auto roughness = (float)j / 5.0f;
                        auto ao = 1.0f;

                        entity.AddComponent<Transform>(pos, glm::vec3(0.0f), glm::vec3(1.0f));
                        entity.AddComponent<MeshRenderer>(
                            Core::Resources::Instance().Load<Core::Model>("Sphere"),
                            albedo, metallic, roughness, ao);
                    }
                }
                 for (int i = 0; i < 4; i++)
                 {
                     auto entity = editorScene->CreateEntity("Light" + std::to_string(i));
                     auto pos = glm::vec3(10.0f, 10.0f, 10.0f);
                     entity.AddComponent<Transform>(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));
                     entity.AddComponent<Core::Scene::Components::Light>(glm::vec3(1.0f, 1.0f, 1.0f), 300.0f);
                 }
            }
            if (ImGui::MenuItem("Add Truck"))
            {
                auto entity = editorScene->CreateEntity("Truck");
                auto pos = glm::vec3(0.0f, 0.0f, 0.0f);
                entity.AddComponent<Transform>(pos, glm::vec3(0.0f), glm::vec3(1.0f));
                entity.AddComponent<MeshRenderer>(
                    Core::Resources::Instance().Load<Core::Model>("models/keytruck/keytruck.obj"),
                    Core::Resources::Instance().Load<Core::TextureAsset>("models/keytruck/keytruck.png"));
            }
            if (ImGui::MenuItem("Add Light"))
            {
                auto entity = editorScene->CreateEntity("Light");
                auto pos = glm::vec3(0.0f, 0.0f, 0.0f);
                entity.AddComponent<Transform>(pos, glm::vec3(0.0f), glm::vec3(1.0f));
                entity.AddComponent<Core::Scene::Components::Light>();
            }
            if (ImGui::MenuItem("Add Sphere"))
            {
                auto entity = editorScene->CreateEntity("Sphere");
                auto pos = glm::vec3(0.0f, 0.0f, 0.0f);
                entity.AddComponent<Transform>(pos, glm::vec3(0.0f), glm::vec3(1.0f));
                entity.AddComponent<MeshRenderer>(
                    Core::Resources::Instance().Load<Core::Model>("Sphere"),
                    Core::Resources::Instance().Load<Core::TextureAsset>("models/keytruck/keytruck.png"));
            }
            if (ImGui::MenuItem("Add Textured Sphere"))
            {
                auto entity = editorScene->CreateEntity("Sphere");
                auto pos = glm::vec3(0.0f, 0.0f, 0.0f);
                entity.AddComponent<Transform>(pos, glm::vec3(0.0f), glm::vec3(1.0f));
                entity.AddComponent<MeshRenderer>(
                    Core::Resources::Instance().Load<Core::Model>("Sphere"),
                    Core::Resources::Instance().Load<Core::TextureAsset>("textures/rustediron2_basecolor.png"),
                    Core::Resources::Instance().Load<Core::TextureAsset>("textures/rustediron2_metallic.png"),
                    Core::Resources::Instance().Load<Core::TextureAsset>("textures/rustediron2_roughness.png"),
                    Core::Resources::Instance().Load<Core::TextureAsset>("textures/rustediron2_basecolor.png"));
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            // if (ImGui::MenuItem("Scene Hierarchy"))
            //     showSceneHierarchy = !showSceneHierarchy;
            // if (ImGui::MenuItem("Inspector"))
            //     showInspector = !showInspector;
            // if (ImGui::MenuItem("Console"))
            //     showConsole = !showConsole;

            if (ImGui::MenuItem("Add Viewport"))
            {
                EditorViewport viewport;
                viewport.framebuffer = Core::Renderer::Framebuffer::Create(1280, 720);
                viewport.camera = CreateRef<Core::Scene::PerspectiveCamera>();

                viewports.push_back(viewport);
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    ImGui::Begin("Entities");

    if (ImGui::BeginListBox("##EntityList", ImVec2(-FLT_MIN, ImGui::GetContentRegionAvail().y)))
    {
        for (Entity entity : ActiveScene->GetAllEntities())
        {
            const bool isSelected = selectedEntity.IsValid() ? entity.GetTag() == selectedEntity.GetTag() : false;
            auto tag = entity.GetTag();
            if (ImGui::Selectable(tag.empty() ? "##" : tag.c_str(), isSelected))
                selectedEntity = entity;

            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }

        ImGui::EndListBox();
    }

    ImGui::End();

    ImGui::Begin("Inspector");

    if (selectedEntity.IsValid())
    {
        if (selectedEntity.HasComponent<Tag>())
        {
            if (ImGui::CollapsingHeader("Tag", ImGuiTreeNodeFlags_DefaultOpen))
            {
                auto& tag = selectedEntity.GetComponent<Tag>();
                ImGui::InputText("##Tag", tag.tag.data(), 1024);
            }
        }

        if (selectedEntity.HasComponent<Position>())
        {
            if (ImGui::CollapsingHeader("Position", ImGuiTreeNodeFlags_DefaultOpen))
            {
                auto& pos = selectedEntity.GetComponent<Position>();

                ImGui::Text("Position");
                ImGui::DragFloat("X", &pos.x);
                ImGui::DragFloat("Y", &pos.y);
            }
        }

        if (selectedEntity.HasComponent<Rect>())
        {
            if (ImGui::CollapsingHeader("Rectangle", ImGuiTreeNodeFlags_DefaultOpen))
            {
                auto& rect = selectedEntity.GetComponent<Rect>();

                ImGui::Text("Rectangle");
                ImGui::DragFloat("Width", &rect.width);
                ImGui::DragFloat("Height", &rect.height);
            }
        }

        if (selectedEntity.HasComponent<RectangleRenderer>())
        {
            if (ImGui::CollapsingHeader("Rectangle Renderer", ImGuiTreeNodeFlags_DefaultOpen))
            {
                auto& rectangleRenderer = selectedEntity.GetComponent<RectangleRenderer>();

                ImVec4* color = (ImVec4*)&rectangleRenderer.color;
                ImGui::Text("Color");
                if (ImGui::ColorButton("Color", *color))
                    ImGui::OpenPopup("##ColorPicker");

                if (ImGui::BeginPopup("##ColorPicker"))
                {
                    ImGui::ColorPicker4("##picker", (float*)color);

                    ImGui::EndPopup();
                }
            }
        }

        if (selectedEntity.HasComponent<LuaScript>())
        {
            if (ImGui::CollapsingHeader("Lua Script", ImGuiTreeNodeFlags_DefaultOpen))
            {
                auto& luaScript = selectedEntity.GetComponent<LuaScript>();
                ImGui::InputTextMultiline("##LuaScript", luaScript.code.data(), 1024,
                                          ImVec2(-FLT_MIN, ImGui::GetContentRegionAvail().y));
            }
        }

        // 3D

        if (selectedEntity.HasComponent<Transform>())
        {
            if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
            {
                auto& transform = selectedEntity.GetComponent<Transform>();
                ImGui::DragFloat3("Position", &transform.position.x, 0.1f);
                ImGui::DragFloat3("Rotation", &transform.rotation.x, 0.1f);
                ImGui::DragFloat3("Scale", &transform.scale.x, 0.1f);
            }
        }

        if (selectedEntity.HasComponent<MeshRenderer>())
        {
            if (ImGui::CollapsingHeader("Mesh Renderer", ImGuiTreeNodeFlags_DefaultOpen))
            {
                auto& meshRenderer = selectedEntity.GetComponent<MeshRenderer>();
                ImGui::Text("Model: %s", meshRenderer.model->GetName().c_str());
                ImGui::SameLine();
                ImGui::Button("Change Model");

                // ImGui::Text("Texture: %s", meshRenderer.texture->GetName().c_str());
                // ImGui::SameLine();
                // ImGui::Button("Change Texture");

                ImGui::ColorEdit3("Albedo", &(meshRenderer.albedo.x));
                ImGui::DragFloat("Metallic", &meshRenderer.metallic, 0.1f, 0.0f, 1.0f);
                ImGui::DragFloat("Roughness", &meshRenderer.roughness, 0.1f, 0.0f, 1.0f);
                ImGui::DragFloat("AO", &meshRenderer.ao, 0.1f, 0.0f, 1.0f);
                // ImGui::InputText("Mesh", meshRenderer.model->GetName(), 1024);
                // ImGui::InputText("Texture", meshRenderer.texture->GetPath(), 1024);
                // ImGui::Checkbox("Enabled", &meshRenderer.enabled);
                // ImGui::Checkbox("Wireframe", &meshRenderer.wireframe);
            }
        }

        if (selectedEntity.HasComponent<Core::Scene::Components::Light>())
        {
            if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
            {
                auto& light = selectedEntity.GetComponent<Core::Scene::Components::Light>();
                ImGui::ColorEdit3("Color", &(light.color.x));
                ImGui::DragFloat("Intensity", &light.intensity, 0.1f, 0.0f, 300.0f);
            }
        }
    }

    ImGui::End();

    ImGui::Begin("Asset Browser");

    ImGui::End();

    auto index = 0;
    for (auto& viewport : viewports)
    {
        ImGui::Begin(("Viewport " + std::to_string(index)).c_str());

        // Draw Viewport
        ImVec2 size = ImGui::GetContentRegionAvail();

        viewport.framebuffer->Resize((uint32_t)size.x, (uint32_t)size.y);
        viewport.camera->SetViewportSize(size.x, size.y);
        ImGui::Image((void*)(intptr_t)viewport.framebuffer->GetColorAttachmentRendererID(), size, ImVec2(0, 1),
                     ImVec2(1, 0));

        if (activeViewportIndex == index)
        {
            // Draw Gizmos
            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();

            ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, size.x, size.y);

            if (ImGui::IsKeyPressed(ImGuiKey_Q)) // z
                gizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
            if (ImGui::IsKeyPressed(ImGuiKey_W)) // e
                gizmoOperation = ImGuizmo::OPERATION::ROTATE;
            if (ImGui::IsKeyPressed(ImGuiKey_E)) // r
                gizmoOperation = ImGuizmo::OPERATION::SCALE;

            auto viewMatrix = viewport.camera->GetViewMatrix();
            auto projectionMatrix = viewport.camera->GetProjectionMatrix();

            if (selectedEntity.IsValid() && selectedEntity.HasComponent<Transform>())
            {
                auto& transform = selectedEntity.GetComponent<Transform>();

                auto translationMatrix = glm::translate(glm::mat4(1.0f), transform.position);
                auto rotationMatrix = glm::toMat4(glm::quat(transform.rotation));
                auto scaleMatrix = glm::scale(glm::mat4(1.0f), transform.scale);

                auto modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
                ImGuizmo::Manipulate(&viewMatrix[0][0], &projectionMatrix[0][0], gizmoOperation, gizmoMode,
                                     &modelMatrix[0][0]);

                switch (gizmoOperation)
                {
                    case ImGuizmo::TRANSLATE:
                        transform.position = glm::vec3(modelMatrix[3]);
                        break;
                    case ImGuizmo::ROTATE:
                        transform.rotation = glm::eulerAngles(glm::quat_cast(modelMatrix));
                        break;
                    case ImGuizmo::SCALE:
                        transform.scale = glm::vec3(glm::length(modelMatrix[0]), glm::length(modelMatrix[1]),
                                                    glm::length(modelMatrix[2]));
                        break;
                    default:
                        break;
                }
            }
        }

        if (ImGui::IsWindowHovered())
        {
            activeViewportIndex = index;

            // Camera controls TODO: Move this logic to a controller
            if (ImGui::IsKeyDown(ImGuiKey_W))
                viewport.camera->SetPosition(viewport.camera->GetPosition() + 0.1f * viewport.camera->GetRotation());
            if (ImGui::IsKeyDown(ImGuiKey_S))
                viewport.camera->SetPosition(viewport.camera->GetPosition() - 0.1f * viewport.camera->GetRotation());
            if (ImGui::IsKeyDown(ImGuiKey_A))
                viewport.camera->SetPosition(
                    viewport.camera->GetPosition() -
                    0.1f * glm::normalize(glm::cross(viewport.camera->GetRotation(), glm::vec3(0.0f, 1.0f, 0.0f))));
            if (ImGui::IsKeyDown(ImGuiKey_D))
                viewport.camera->SetPosition(
                    viewport.camera->GetPosition() +
                    0.1f * glm::normalize(glm::cross(viewport.camera->GetRotation(), glm::vec3(0.0f, 1.0f, 0.0f))));

            if (ImGui::IsKeyPressed(ImGuiKey_Space))
                viewport.camera->SetPosition(viewport.camera->GetPosition() + glm::vec3(0.0f, 1.0f, 0.0f));

            if (ImGui::IsMouseDragging(ImGuiMouseButton_Right))
            {
                auto mouseDelta = ImGui::GetIO().MouseDelta;
                viewport.yaw += mouseDelta.x * 0.10f;
                viewport.pitch -= mouseDelta.y * 0.10f;

                if (viewport.pitch > 89.0f)
                    viewport.pitch = 89.0f;

                if (viewport.pitch < -89.0f)
                    viewport.pitch = -89.0f;

                glm::vec3 direction;
                direction.x = cos(glm::radians(viewport.yaw)) * cos(glm::radians(viewport.pitch));
                direction.y = sin(glm::radians(viewport.pitch));
                direction.z = sin(glm::radians(viewport.yaw)) * cos(glm::radians(viewport.pitch));
                viewport.camera->SetRotation(direction);
            }
        }

        ImGui::End();
        index++;
    }

    ImGui::Begin("Project Settings");
    ImGui::End();

    ImGui::Begin("Console");
    for (auto& msg : Core::Log::GetAllLogs())
    {
        ImGui::Text("%s", msg.data());
        // ImGui::TextColored(imgui_sink->to_imgui_color(msg.level), "[%s] %s",
        // spdlog::level::to_string_view(msg.level), msg.payload.data());
    }
    ImGui::SetScrollHereY(1.0f);
    ImGui::End();

    EditorLayer::EndImGui();
}

void EditorLayer::DrawScene()
{
    for (const auto& viewport : viewports)
    {
        viewport.framebuffer->Bind();
        ActiveScene->SetCamera(viewport.camera);
        Core::Renderer::RenderCommand::Clear();
        ActiveScene->OnDraw();
        // ApplicationLayer::OnDraw(); // Draws Scenes
        viewport.framebuffer->Unbind();
    }
}

EditorLayer::EditorLayer()
{
    Name = "SignEditor Layer";
}
} // namespace SignE::Editor::Application
