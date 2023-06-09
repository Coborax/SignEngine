//
// Created by Mikkel Mouridsen on 13/01/2023.
//

#ifndef SIGNEPROJECT_ENTITY_H
#define SIGNEPROJECT_ENTITY_H


#include <string>
#include <flecs.h>

#include "Scene/SceneSerializer.h"
#include "Scene.h"
#include "Components.h"
#include "Log.h"

namespace SignE::Core::Scene {
    using namespace SignE::Core::Scene::Components;

    class Entity {
    public:
        Entity() = default;
        Entity(flecs::entity entityHandle, Scene* scene) : entityHandle(entityHandle), scene(scene) {};

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args) {
            T component(std::forward<Args>(args)...); 
            entityHandle.set<T>(component);
            return *entityHandle.get_mut<T>();
        }

        template<typename T>
        void RemoveComponent() {
            entityHandle.remove<T>();
        }

        template<typename T>
        T& GetComponent() {
            return *entityHandle.get_mut<T>();
        }

        template<typename T>
        bool HasComponent() {
            return entityHandle.has<T>();
        }

        std::string& GetTag() {
            if (entityHandle.has<Tag>()) {
                return entityHandle.get_mut<Tag>()->tag;
            }
            else {
                entityHandle.set<Tag>(Tag());
                return entityHandle.get_mut<Tag>()->tag;
            }
        }

        bool IsValid() {
            if (scene == nullptr) {
                return false;
            }
            return entityHandle.is_valid() && entityHandle.is_alive();
        }

        friend class SceneSerializer;

    private:
        flecs::entity entityHandle;
        Scene* scene;
    };
}
#endif //SIGNEPROJECT_ENTITY_H
