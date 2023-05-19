//
// Created by Mikkel Mouridsen on 19/12/2022.
//

#ifndef SIGNEPROJECT_EDITORLAYER_H
#define SIGNEPROJECT_EDITORLAYER_H


#include "Application/ImGuiLayer.h"
#include "Scene/Entity.h"
#include <memory>
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
    private:
        Ref<Scene> editorScene;
        Ref<Scene> playScene;

        Entity selectedEntity;
    };
}


#endif //SIGNEPROJECT_EDITORLAYER_H
