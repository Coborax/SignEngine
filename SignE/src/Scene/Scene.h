//
// Created by Mikkel Mouridsen on 18/12/2022.
//

#ifndef SIGNEPROJECT_SCENE_H
#define SIGNEPROJECT_SCENE_H

#include <utility>

#include "entt/entt.hpp"
#include "../Log.h"

class Entity;

class Scene {
public:
    Scene() : name("Scene") {};
    Scene(std::string name) : name(std::move(name)) {};

    void OnInit();
    void OnUpdate(float dt);
    void OnDraw();
    void OnShutdown();

    Entity CreateEntity(std::string tag);
    Entity GetEntityByTag(std::string tag);
    std::vector<Entity> GetAllEntities();

    friend class Entity;

private:
    entt::registry registry;
    std::unordered_map<std::string, entt::entity> entityMap;

    std::string name;
};


#endif //SIGNEPROJECT_SCENE_H
