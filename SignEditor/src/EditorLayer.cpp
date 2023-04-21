//
// Created by Mikkel Mouridsen on 19/12/2022.
//

#include "EditorLayer.h"
#include "Renderer/Renderer2D.h"
#include "Scene/Entity.h"
#include "Scene/Components.h"
#include "Scripting/LuaScriptEngine.h"
#include "imgui.h"

namespace SignE::Editor::Application {
    using SignE::Core::Renderer::Renderer2D;
    using SignE::Core::Scene::Components::RectangleRenderer;
    using SignE::Core::Scene::Components::Position;
    using SignE::Core::Scene::Components::Rect;
    using SignE::Core::Scene::Components::LuaScript;
    using SignE::Core::Scripting::LuaScriptEngine;

    void EditorLayer::OnInit() {
        ImGuiLayer::OnInit();
        Renderer2D::InitRenderTexture();

        LuaScriptEngine::Pause();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        SetActiveScene(&editorScene);
    }

    void EditorLayer::OnDraw() {
        DrawScene();
        DrawUI();
    }

    void EditorLayer::OnShutdown() {
        ImGuiLayer::OnShutdown();
        Renderer2D::CleanupRenderTexture();
    }

    void EditorLayer::DrawUI() {
        Renderer2D::BeginDraw();
        EditorLayer::BeginImGui();
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        ImGui::Begin("Entities");

        if (ImGui::BeginListBox("##EntityList", ImVec2(-FLT_MIN, ImGui::GetContentRegionAvail().y))) {
            for (Entity entity: ActiveScene->GetAllEntities()) {
                const bool isSelected = entity.GetTag() == selectedEntity.GetTag();
                if (ImGui::Selectable(entity.GetTag().c_str(), isSelected))
                    selectedEntity = entity;

                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndListBox();
        }

        ImGui::End();

        ImGui::Begin("Inspector");

        if (selectedEntity.GetTag() != "") {
            ImGui::Text("%s", selectedEntity.GetTag().c_str());
            ImGui::Separator();

            if (selectedEntity.HasComponent<Position>()) {
                if (ImGui::CollapsingHeader("Position", ImGuiTreeNodeFlags_DefaultOpen)) {
                    auto& pos = selectedEntity.GetComponent<Position>();

                    ImGui::Text("Position");
                    ImGui::DragFloat("X", &pos.x);
                    ImGui::DragFloat("Y", &pos.y);
                }
            }

            if (selectedEntity.HasComponent<Rect>()) {
                if (ImGui::CollapsingHeader("Rectangle", ImGuiTreeNodeFlags_DefaultOpen)) {
                    auto& rect = selectedEntity.GetComponent<Rect>();

                    ImGui::Text("Rectangle");
                    ImGui::DragFloat("Width", &rect.width);
                    ImGui::DragFloat("Height", &rect.height);
                }
            }

            if (selectedEntity.HasComponent<RectangleRenderer>()) {
                if (ImGui::CollapsingHeader("Rectangle Renderer", ImGuiTreeNodeFlags_DefaultOpen)) {
                    auto& rectangleRenderer = selectedEntity.GetComponent<RectangleRenderer>();

                    // Moved to own component 
                    // ImGui::Text("Rectangle");
                    // ImGui::DragFloat("Width", &rectangleRenderer.rect.width);
                    // ImGui::DragFloat("Height", &rectangleRenderer.rect.height);

                    ImVec4* color = (ImVec4*) &rectangleRenderer.color;
                    ImGui::Text("Color");
                    if (ImGui::ColorButton("Color", *color))
                        ImGui::OpenPopup("##ColorPicker");

                    if (ImGui::BeginPopup("##ColorPicker")) {

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
                    char* code = const_cast<char*>(luaScript.code.c_str()); 
                    ImGui::InputTextMultiline("Code", code, 100);

                    if (ImGui::Button("Run Code")) {
                        LuaScriptEngine::RunScript(code);
                    }
                }
            }
        }

        ImGui::End();

        ImGui::Begin("Asset Browser");

        ImGui::End();

        ImGui::Begin("Scene View");

        // Draw Viewport
        ImVec2 size = ImGui::GetContentRegionAvail();
        Renderer2D::ImGuiDrawRenderTexture(size.x, size.y);

        ImGui::End();

        ImGui::Begin("Project Settings");
        ImGui::End();

        EditorLayer::EndImGui();
        Renderer2D::EndDraw();
    }

    void EditorLayer::DrawScene() {
        Renderer2D::BeginDrawRenderTexture();
        Renderer2D::DrawFPS();
        ApplicationLayer::OnDraw(); // Draws Scenes
        Renderer2D::EndDrawRenderTexture();
    }

    EditorLayer::EditorLayer() {
        Name = "SignEditor Layer";
    }
}
