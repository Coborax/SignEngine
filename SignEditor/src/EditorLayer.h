//
// Created by Mikkel Mouridsen on 19/12/2022.
//

#ifndef SIGNEPROJECT_EDITORLAYER_H
#define SIGNEPROJECT_EDITORLAYER_H


#include "Application/ImGuiLayer.h"
#include "Scene/Entity.h"
#include <ImGuizmo.h>
#include <memory>

namespace SignE::Core::Renderer {
    class Framebuffer;
}

namespace SignE::Editor::Application {
    using SignE::Core::Scene::Scene;
    using SignE::Core::Scene::Entity;
    using SignE::Core::Application::ImGuiLayer;

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
        Ref<Core::Renderer::Framebuffer> framebuffer;
        Ref<Scene> editorScene;
        Ref<Scene> playScene;

        Entity selectedEntity;
        ImGuizmo::MODE gizmoMode = ImGuizmo::MODE::LOCAL;
        ImGuizmo::OPERATION gizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
    };
}


#endif //SIGNEPROJECT_EDITORLAYER_H
