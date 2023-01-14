//
// Created by Mikkel Mouridsen on 19/12/2022.
//

#include "EditorLayer.h"
#include "Renderer/Renderer2D.h"
#include "Scene/Entity.h"
#include "Scene/Components.h"

void EditorLayer::OnInit() {
    ImGuiLayer::OnInit();
    Renderer2D::InitRenderTexture();

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

        if (ImGui::CollapsingHeader("Position", ImGuiTreeNodeFlags_DefaultOpen)) {
            if (selectedEntity.HasComponent<Position>()) {
                auto& pos = selectedEntity.GetComponent<Position>();

                ImGui::Text("Position");
                ImGui::DragFloat("X", &pos.x);
                ImGui::DragFloat("Y", &pos.y);
            }
        }

        if (ImGui::CollapsingHeader("Rectangle Renderer", ImGuiTreeNodeFlags_DefaultOpen)) {
            if (selectedEntity.HasComponent<RectangleRenderer>()) {
                auto& rectangleRenderer = selectedEntity.GetComponent<RectangleRenderer>();

                ImGui::Text("Position");
                ImGui::DragFloat("Width", &rectangleRenderer.width);
                ImGui::DragFloat("Height", &rectangleRenderer.height);

                ImVec4* color = (ImVec4*) &rectangleRenderer.color;
                if (ImGui::ColorButton("Color", *color))
                    ImGui::OpenPopup("##ColorPicker");

                if (ImGui::BeginPopup("##ColorPicker")) {

                    ImGui::ColorPicker4("##picker", (float*)color);

                    ImGui::EndPopup();
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

