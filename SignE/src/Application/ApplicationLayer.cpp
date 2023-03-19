//
// Created by Mikkel Mouridsen on 17/12/2022.
//

#include "ApplicationLayer.h"

namespace SignE::Core::Application {
    void ApplicationLayer::OnInit() {
        Log::LogInfo("OnInit Application Layer: " + Name);
    }

    void ApplicationLayer::OnUpdate(float dt) {
        if (ActiveScene)
            ActiveScene->OnUpdate(dt);
    }

    void ApplicationLayer::OnDraw() {
        if (ActiveScene)
            ActiveScene->OnDraw();
    }

    void ApplicationLayer::SetActiveScene(Scene*scene) {
        if (std::find(scenes.begin(), scenes.end(), scene) == scenes.end())
            scenes.push_back(scene);

        ActiveScene = scene;
        ActiveScene->OnInit();
    }

    void ApplicationLayer::OnShutdown() {
        Log::LogInfo("OnShutdown Application Layer: " + Name);
        for (Scene* scene : scenes) {
            scene->OnShutdown();
        }
    }
}