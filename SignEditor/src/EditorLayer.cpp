//
// Created by Mikkel Mouridsen on 19/12/2022.
//

#include "EditorLayer.h"
#include "Renderer/Renderer2D.h"

void EditorLayer::OnInit() {
    ImGuiLayer::OnInit();
    Renderer2D::InitRenderTexture();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void EditorLayer::OnDraw() {

    Renderer2D::BeginDrawRenderTexture();
    Renderer2D::DrawRect(200, 200);
    Renderer2D::EndDrawRenderTexture();

    Renderer2D::BeginDraw();
    EditorLayer::BeginImGui();
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    ImGui::Begin("Inspector");

    ImGui::End();

    ImGui::Begin("Asset Browser");

    ImGui::End();

    ImGui::Begin("Scene View");

    ImVec2 size = ImGui::GetContentRegionAvail();
    Renderer2D::ImGuiDrawRenderTexture(size.x, size.y);

    ImGui::End();

    ImGui::Begin("Project Settings");

    ImGui::End();

    EditorLayer::EndImGui();
    Renderer2D::EndDraw();
}

void EditorLayer::OnShutdown() {
    ImGuiLayer::OnShutdown();
    Renderer2D::CleanupRenderTexture();
}

