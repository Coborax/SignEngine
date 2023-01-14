//
// Created by Mikkel Mouridsen on 18/12/2022.
//

#include "Scene.h"

#include <utility>
#include "../Renderer/Renderer2D.h"
#include "Entity.h"
#include "Components.h"

void Scene::OnInit() {
    Log::LogInfo("OnInit Scene: " + name);

    CreateEntity("Test Entity");
    CreateEntity("Test Entity 2");
}

void Scene::OnUpdate(float dt) {

}

void Scene::OnDraw() {

    // Draw Rectangles
    auto view = registry.view<Position, RectangleRenderer>();
    for(auto entity: view) {
        auto& pos = view.get<Position>(entity);
        auto& box = view.get<RectangleRenderer>(entity);
        Renderer2D::DrawRect(pos.x, pos.y, box.width, box.height, box.color.r, box.color.g, box.color.b, box.color.a);
    }

}

void Scene::OnShutdown() {
    Log::LogInfo("OnShutdown Scene: " + name);
}

Entity Scene::CreateEntity(std::string tag) {
    auto entityHandle = registry.create();

    Entity entity = {entityHandle, tag, this };
    entity.AddComponent<Position>(100.0f, 100.0f);
    entity.AddComponent<RectangleRenderer>(10.0f, 10.0f);

    entityMap[tag] = entityHandle;

    return entity;
}

Entity Scene::GetEntityByTag(std::string tag) {
    if (entityMap.find(tag) != entityMap.end())
        return { entityMap.at(tag), tag, this };
}

std::vector<Entity> Scene::GetAllEntities() {
    std::vector<Entity> result;

    for (auto const& [tag, entity] : entityMap)
        result.emplace_back(entity, tag, this);

    return result;
}
