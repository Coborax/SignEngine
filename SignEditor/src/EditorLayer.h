//
// Created by Mikkel Mouridsen on 19/12/2022.
//

#ifndef SIGNEPROJECT_EDITORLAYER_H
#define SIGNEPROJECT_EDITORLAYER_H


#include "Application/ImGuiLayer.h"
#include "Scene/Entity.h"

class EditorLayer : public ImGuiLayer {
public:
    void OnInit() override;
    void OnDraw() override;
    void OnShutdown() override;

    void DrawUI();
    void DrawScene();
private:
    Scene editorScene;
    Scene playScene;

    Entity selectedEntity;
};


#endif //SIGNEPROJECT_EDITORLAYER_H
