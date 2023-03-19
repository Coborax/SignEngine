//
// Created by Mikkel Mouridsen on 13/01/2023.
//

#ifndef SIGNEPROJECT_ENTITY_H
#define SIGNEPROJECT_ENTITY_H


#include <string>
#include "entt/entt.hpp"
#include "Scene.h"

namespace SignE::Core::Scene {
    class Entity {
    public:
        Entity() = default;
        Entity(entt::entity entityHandle, std::string tag, Scene* scene) : entityHandle(entityHandle), tag(tag), scene(scene) {};

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args) {
            return scene->registry.emplace<T>(entityHandle, std::forward<Args>(args)...);
        }

        template<typename T>
        T& GetComponent() {
            return scene->registry.get<T>(entityHandle);
        }

        template<typename T>
        bool HasComponent() {
            return scene->registry.any_of<T>(entityHandle);
        }

        std::string GetTag() {
            return tag;
        }

    private:
        std::string tag;
        entt::entity entityHandle;
        Scene* scene;
    };
}
#endif //SIGNEPROJECT_ENTITY_H
