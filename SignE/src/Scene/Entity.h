//
// Created by Mikkel Mouridsen on 13/01/2023.
//

#ifndef SIGNEPROJECT_ENTITY_H
#define SIGNEPROJECT_ENTITY_H


#include <string>
#include "Scene/SceneSerializer.h"
#include "entt/entt.hpp"
#include "Scene.h"
#include "Components.h"
#include "Log.h"

namespace SignE::Core::Scene {
    using namespace SignE::Core::Scene::Components;

    class Entity {
    public:
        Entity() = default;
        Entity(entt::entity entityHandle, Scene* scene) : entityHandle(entityHandle), scene(scene) {};

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
            if (HasComponent<Tag>()) {
                return GetComponent<Tag>().tag;
            }
            return "";
        }

        bool IsValid() {
            if (scene == nullptr) {
                return false;
            }
            return scene->registry.valid(entityHandle);
        }

        friend class SceneSerializer;

    private:
        entt::entity entityHandle;
        Scene* scene;
    };
}
#endif //SIGNEPROJECT_ENTITY_H
