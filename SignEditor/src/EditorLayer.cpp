//
// Created by Mikkel Mouridsen on 19/12/2022.
//

#include "EditorLayer.h"
#include "Renderer/Renderer2D.h"
#include "Scene/Entity.h"
#include "Scene/Components.h"
#include "Scripting/LuaScriptEngine.h"
#include "Scene/SceneSerializer.h"
#include "imgui.h"
#include <memory>

namespace SignE::Editor::Application
{
using SignE::Core::Renderer::Renderer2D;
using SignE::Core::Scene::SceneSerializer;
using SignE::Core::Scene::Components::LuaScript;
using SignE::Core::Scene::Components::Position;
using SignE::Core::Scene::Components::Rect;
using SignE::Core::Scene::Components::RectangleRenderer;
using SignE::Core::Scene::Components::Tag;

void EditorLayer::OnInit()
{
    ImGuiLayer::OnInit();
    Renderer2D::InitRenderTexture();

    Core::Log::SetupInMemoryLog();

    // ImGuiIO &io = ImGui::GetIO();
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    editorScene = CreateRef<Scene>();
    SetActiveScene(editorScene);
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

void EditorLayer::DrawUI()
{
    EditorLayer::BeginImGui();

    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

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

                auto path = "test.yaml";
                serializer.Serialize(path);
            }
            if (ImGui::MenuItem("Save Scene"))
            {
                SceneSerializer serializer(editorScene);

                auto path = "test.yaml";
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
                entity.AddComponent<Position>();
                entity.AddComponent<Rect>();
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
    }

    ImGui::End();

    ImGui::Begin("Asset Browser");

    ImGui::End();

    ImGui::Begin("Scene View");

    // Draw Viewport
    ImVec2 size = ImGui::GetContentRegionAvail();

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
    ApplicationLayer::OnDraw(); // Draws Scenes
}

EditorLayer::EditorLayer()
{
    Name = "SignEditor Layer";
}
} // namespace SignE::Editor::Application
