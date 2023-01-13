//
// Created by Mikkel Mouridsen on 18/12/2022.
//

#include "ImGuiLayer.h"
#include "Renderer/Renderer2D.h"

void ImGuiLayer::OnInit() {
    ApplicationLayer::OnInit();
    rlImGuiSetup(true);
}

void ImGuiLayer::OnUpdate(float dt) {
    ApplicationLayer::OnUpdate(dt);
}

void ImGuiLayer::OnDraw() {
    BeginImGui();
    ImGui::ShowDemoWindow();
    ImGui::ShowAboutWindow();
    EndImGui();
}

void ImGuiLayer::OnShutdown() {
    ApplicationLayer::OnShutdown();
    Renderer2D::CleanupImGui();
}

ImGuiLayer::ImGuiLayer() {
    Name = "ImGui Application Layer";
}

void ImGuiLayer::BeginImGui() {
    Renderer2D::BeginImGui();
}

void ImGuiLayer::EndImGui() {
    Renderer2D::EndImGui();
}


