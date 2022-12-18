//
// Created by Mikkel Mouridsen on 17/12/2022.
//

#include "ApplicationLayer.h"

void ApplicationLayer::OnInit() {
    Log::LogInfo("Initializing Application Layer: " + Name);
}

void ApplicationLayer::OnUpdate(float dt) {
    if (activeScene)
        activeScene->OnUpdate(dt);
}

void ApplicationLayer::OnDraw() {
    if (activeScene)
        activeScene->OnDraw();
}

void ApplicationLayer::SetActiveScene(Scene *scene) {
    activeScene = scene;
    activeScene->OnInit();
}
