//
// Created by Mikkel Mouridsen on 18/12/2022.
//

#include "Scene.h"

#include <utility>

#include "../Renderer/Renderer2D.h"
#include "Entity.h"
#include "Components.h"
#include "Scripting/LuaScriptEngine.h"
#include "raylib.h"


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

        CreateEntity("Test Entity");
        CreateEntity("Test Entity 2");
    }

    void Scene::OnUpdate(float dt) {
        // Run Lua Scripts 
        if (!LuaScriptEngine::IsPaused()) {
            auto view = registry.view<LuaScript>();
            for (auto entity : view) {
                auto& luaScript = view.get<LuaScript>(entity);
                LuaScriptEngine::RunScript(luaScript.code);
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

        Entity entity = {entityHandle, tag, this };
        entity.AddComponent<Position>(100.0f, 100.0f);
        auto& rect = entity.AddComponent<Rect>(100.0f, 100.0f);
        entity.AddComponent<RectangleRenderer>(rect, Color{ 0.529f, 0.808f, 0.922f, 1.0f });

        entity.AddComponent<LuaScript>("print('Hello from Lua!')");

        entityMap[tag] = entityHandle;

        return entity;
    }

    Entity Scene::GetEntityByTag(std::string tag) {
        if (entityMap.find(tag) != entityMap.end())
            return { entityMap.at(tag), tag, this };
        return {};
    }

    std::vector<Entity> Scene::GetAllEntities() {
        std::vector<Entity> result;

        for (auto const& [tag, entity] : entityMap)
            result.emplace_back(entity, tag, this);

        return result;
    }
}

