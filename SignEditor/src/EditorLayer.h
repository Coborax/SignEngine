//
// Created by Mikkel Mouridsen on 19/12/2022.
//

#ifndef SIGNEPROJECT_EDITORLAYER_H
#define SIGNEPROJECT_EDITORLAYER_H


#include "Application/ImGuiLayer.h"
#include "Renderer/Framebuffer.h"
#include "Scene/Entity.h"
#include "Scene/Scene.h"
#include <ImGuizmo.h>
#include <imgui.h>
#include <memory>
#include <vector>

namespace SignE::Core::Renderer {
    class Framebuffer;
}

namespace SignE::Editor::Application {
    using SignE::Core::Scene::Scene;
    using SignE::Core::Scene::Entity;
    using SignE::Core::Application::ImGuiLayer;

    struct EditorViewport {
        Ref<Core::Renderer::Framebuffer> framebuffer;
        Ref<Core::Scene::Camera> camera;
        float pitch = 0.0f, yaw = 0.0f;
        bool isActive = true;
    };

    class EditorLayer : public ImGuiLayer {
    public:
        EditorLayer();

        void OnInit() override;
        void OnDraw() override;
        void OnShutdown() override;

        void DrawUI();
        void DrawScene();
        void DrawGrid();
    private:
        Ref<Scene> editorScene;
        Ref<Scene> playScene;

        std::vector<EditorViewport> viewports;
        int activeViewportIndex = 0;

        Entity selectedEntity;
        ImGuizmo::MODE gizmoMode = ImGuizmo::MODE::LOCAL;
        ImGuizmo::OPERATION gizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
    };
}


#endif //SIGNEPROJECT_EDITORLAYER_H
