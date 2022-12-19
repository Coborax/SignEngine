//
// Created by Mikkel Mouridsen on 18/12/2022.
//

#ifndef SIGNEPROJECT_IMGUILAYER_H
#define SIGNEPROJECT_IMGUILAYER_H

#include "imgui.h"
#include "../includes/rlImGui/rlImGui.h"

#include "ApplicationLayer.h"

class ImGuiLayer : public ApplicationLayer {
public:
    ImGuiLayer();

    void BeginImGui();
    void EndImGui();

    void OnInit() override;
    void OnUpdate(float dt) override;
    void OnDraw() override;
    void OnShutdown() override;
};


#endif //SIGNEPROJECT_IMGUILAYER_H
