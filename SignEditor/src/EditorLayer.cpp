//
// Created by Mikkel Mouridsen on 19/12/2022.
//

#include "EditorLayer.h"

#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"
#include "Scene/Entity.h"
#include "Scene/Components.h"
#include "Scripting/LuaScriptEngine.h"
#include "Scene/SceneSerializer.h"
#include "Renderer/Framebuffer.h"

#include <_types/_uint32_t.h>
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

    framebuffer = Core::Renderer::Framebuffer::Create(1280, 720);
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
            if (ImGui::MenuItem("Add Example Entity"))
            {
                auto entity = editorScene->CreateEntity("Entity");
                entity.AddComponent<Transform>();
                entity.AddComponent<MeshRenderer>("models/keytruck/keytruck.obj", "models/keytruck/keytruck.png");
            }
            if (ImGui::MenuItem("Add Example Entity 2"))
            {
                auto entity = editorScene->CreateEntity("Entity");
                entity.AddComponent<Transform>();
                entity.AddComponent<MeshRenderer>("models/VikingRoom/viking_room.obj",
                                                  "models/VikingRoom/viking_room.png");
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
                auto meshRenderer = selectedEntity.GetComponent<MeshRenderer>();
                ImGui::InputText("Mesh", meshRenderer.modelPath.data(), 1024);
                ImGui::InputText("Texture", meshRenderer.texturePath.data(), 1024);
                // ImGui::Checkbox("Enabled", &meshRenderer.enabled);
                // ImGui::Checkbox("Wireframe", &meshRenderer.wireframe);
            }
        }
    }

    ImGui::End();

    ImGui::Begin("Asset Browser");

    ImGui::End();

    ImGui::Begin("Viewport");

    // Draw Viewport
    ImVec2 size = ImGui::GetContentRegionAvail();

    framebuffer->Resize((uint32_t)size.x, (uint32_t)size.y);
    ActiveScene->GetCamera()->SetViewportSize(size.x, size.y);
    ImGui::Image((void*)(intptr_t)framebuffer->GetColorAttachmentRendererID(), size, ImVec2(0, 1), ImVec2(1, 0));

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

    auto viewMatrix = editorScene->GetCamera()->GetViewMatrix();
    auto projectionMatrix = editorScene->GetCamera()->GetProjectionMatrix();

    if (selectedEntity.IsValid() && selectedEntity.HasComponent<Transform>())
    {
        auto& transform = selectedEntity.GetComponent<Transform>();

        auto translationMatrix = glm::translate(glm::mat4(1.0f), transform.position);
        auto rotationMatrix = glm::toMat4(glm::quat(transform.rotation));
        auto scaleMatrix = glm::scale(glm::mat4(1.0f), transform.scale);

        auto modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
        ImGuizmo::Manipulate(&viewMatrix[0][0], &projectionMatrix[0][0], gizmoOperation, gizmoMode, &modelMatrix[0][0]);

        switch (gizmoOperation)
        {
            case ImGuizmo::TRANSLATE:
                transform.position = glm::vec3(modelMatrix[3]);
                break;
            case ImGuizmo::ROTATE:
                transform.rotation = glm::eulerAngles(glm::quat_cast(modelMatrix));
                break;
            case ImGuizmo::SCALE:
                transform.scale =
                    glm::vec3(glm::length(modelMatrix[0]), glm::length(modelMatrix[1]), glm::length(modelMatrix[2]));
                break;
                break;
            default:
                break;
        }
    }

    ImGui::End();

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
    framebuffer->Bind();
    Core::Renderer::RenderCommand::Clear();
    ActiveScene->OnDraw();
    // ApplicationLayer::OnDraw(); // Draws Scenes
    framebuffer->Unbind();
}

EditorLayer::EditorLayer()
{
    Name = "SignEditor Layer";
}
} // namespace SignE::Editor::Application
