//
// Created by Mikkel Mouridsen on 18/12/2022.
//

#include "Scene.h"

#include <utility>

#include "../Renderer/Renderer2D.h"
#include "Entity.h"
#include "Components.h"
#include "Scripting/LuaScriptEngine.h"

namespace SignE::Core::Scene {
    using Renderer::Renderer2D;

    using Components::RectangleRenderer;
    using Components::Position;
    using Components::Rect;
    using Components::Color;
    using Components::LuaScript;

    using Scripting::LuaScriptEngine;

    void Scene::OnInit() {
        Log::LogInfo("OnInit Scene: " + name);
    }

    void Scene::OnUpdate(float dt) {
        // Run Lua Scripts 
        if (!LuaScriptEngine::IsPaused()) {
            auto view = registry.view<LuaScript>();
            for (auto entity : view) {
                auto& luaScript = view.get<LuaScript>(entity);
                LuaScriptEngine::RunUpdateFunction({ entity, this }, luaScript.code);
            }
        }
    }

    void Scene::OnDraw() {
        // Draw Rectangles
        auto view = registry.view<Position, RectangleRenderer>();
        for(auto entity: view) {
            auto& rectRenderer = view.get<RectangleRenderer>(entity);

            auto& pos = view.get<Position>(entity);
            auto& rect = rectRenderer.rect;
            auto& color = rectRenderer.color;

            Renderer2D::DrawRect(pos.x, pos.y, rect.width, rect.height, color.r, color.g, color.b, color.a);
        }
    }

    void Scene::OnShutdown() {
        Log::LogInfo("OnShutdown Scene: " + name);
    }

    Entity Scene::CreateEntity(std::string tag) {
        auto entityHandle = registry.create();

        Entity entity = { entityHandle, this };
        entityMap[tag] = entityHandle;

        entity.AddComponent<Tag>(tag);

        return entity;
    }

    Entity Scene::GetEntityByTag(std::string tag) {
        if (entityMap.find(tag) != entityMap.end())
            return { entityMap.at(tag), this };
        return {};
    }

    std::vector<Entity> Scene::GetAllEntities() {
        std::vector<Entity> entities;

        auto view = registry.view<Tag>();
        for (auto entity : view) {
            entities.push_back({ entity, this });
        }

        return entities;
    }
}

