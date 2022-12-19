//
// Created by Mikkel Mouridsen on 18/12/2022.
//

#include "Scene.h"
#include "../Renderer/Renderer2D.h"

Scene::Scene() {
    this->name = "Scene";
}

Scene::Scene(std::string name) {
    this->name = name;
}

void Scene::OnInit() {
    Log::LogInfo("OnInit Scene: " + name);
}

void Scene::OnUpdate(float dt) {

}

void Scene::OnDraw() {
    Renderer2D::DrawRect(10, 10);
}

void Scene::OnShutdown() {
    Log::LogInfo("OnShutdown Scene: " + name);
}
