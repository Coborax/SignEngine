//
// Created by Mikkel Mouridsen on 18/12/2022.
//

#include "ImGuiLayer.h"
#include "Renderer/Renderer2D.h"

using Renderer2D = SignE::Core::Renderer::Renderer2D;

namespace SignE::Core::Application {
    void ImGuiLayer::OnInit() {
        ApplicationLayer::OnInit();
        rlImGuiSetup(true);
    }

    void ImGuiLayer::OnUpdate(float dt) {
        ApplicationLayer::OnUpdate(dt);
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
}


