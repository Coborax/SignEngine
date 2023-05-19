//
// Created by Mikkel Mouridsen on 17/12/2022.
//

#include "ApplicationLayer.h"
#include "Log.h"
#include "Scene/Scene.h"
#include <memory>

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

    void ApplicationLayer::SetActiveScene(const Ref<Scene>& scene) {
        scenes.push_back(scene);

        ActiveScene = scene;
        ActiveScene->OnInit();
    }

    void ApplicationLayer::OnShutdown() {
        Log::LogInfo("OnShutdown Application Layer: " + Name);
        for (auto scene : scenes) {
            scene->OnShutdown();
        }
    }
}
