//
// Created by Mikkel Mouridsen on 17/12/2022.
//

#include "ApplicationLayer.h"

void ApplicationLayer::OnInit() {
    Log::LogInfo("OnInit Application Layer: " + Name);
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

void ApplicationLayer::OnShutdown() {
    Log::LogInfo("OnShutdown Application Layer: " + Name);
    for (Scene* scene : scenes) {
        scene->OnShutdown();
    }
}
