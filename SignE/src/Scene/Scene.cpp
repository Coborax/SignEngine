//
// Created by Mikkel Mouridsen on 18/12/2022.
//

#include "Scene.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <utility>

#include "../Renderer/Renderer2D.h"
#include "../Renderer/Renderer3D.h"
#include "../Renderer/Renderer.h"
#include "Log.h"
#include "Renderer/Texture.h"
#include "Resources/Resources.h"
#include "Entity.h"
#include "Components.h"
#include "Resources/Texture.h"
#include "Scripting/LuaScriptEngine.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace SignE::Core::Scene
{
using Renderer::Renderer2D;

using Components::Color;
using Components::LuaScript;
using Components::Position;
using Components::Rect;
using Components::RectangleRenderer;

using Components::MeshRenderer;
using Components::Transform;

using Scripting::LuaScriptEngine;

void Scene::OnInit()
{
    Log::LogInfo("OnInit Scene: " + name);
}

void Scene::OnUpdate(float dt)
{
    // Run Lua Scripts
    if (!LuaScriptEngine::IsPaused())
    {
        auto luaScriptFilter = ecsWorld.filter<LuaScript>();
        luaScriptFilter.each(
            [this](flecs::entity entity, LuaScript& luaScript) {
                LuaScriptEngine::RunUpdateFunction({entity, this}, luaScript.code);
            });
    }
}

void Scene::OnDraw()
{
    // Draw Rectangles
    auto rectangleRendererFilter = ecsWorld.filter<RectangleRenderer, Position>();
    rectangleRendererFilter.each(
        [](flecs::entity entity, RectangleRenderer& rectangleRenderer, Position& position)
        {
            auto& rect = rectangleRenderer.rect;
            auto& color = rectangleRenderer.color;

            Renderer2D::DrawRect(position.x, position.y, rect.width, rect.height, color.r, color.g, color.b, color.a);
        });
    // for (auto entity : view)
    // {
    //     auto& rectRenderer = view.get<RectangleRenderer>(entity);
    //
    //     auto& pos = view.get<Position>(entity);
    //     auto& rect = rectRenderer.rect;
    //     auto& color = rectRenderer.color;
    //
    //     Renderer2D::DrawRect(pos.x, pos.y, rect.width, rect.height, color.r, color.g, color.b, color.a);
    // }

    // Draw Models

    // TODO: Add Scene Camera (Maybe both Editor and Game Camera)
    // auto viewMatrix = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    // auto projectionMatrix = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
    //

    // Set lights
    auto lightFilter = ecsWorld.filter<Light, Transform>();
    lightFilter.each([](flecs::entity entity, Light& light, Transform& transform)
                     { Renderer::Renderer3D::AddLight(transform.position, light.GetColor()); });

    // auto modelView = registry.view<Transform, MeshRenderer>();
    Renderer::Renderer3D::Begin(camera->GetViewMatrix(), camera->GetProjectionMatrix(), camera->GetPosition());

    Renderer::Renderer3D::DrawGrid();

    auto meshRendererFilter = ecsWorld.filter<MeshRenderer, Transform>();
    meshRendererFilter.each(
        [](flecs::entity entity, MeshRenderer& meshRenderer, Transform& transform)
        {
            auto model = meshRenderer.model;

            auto translationMatrix = glm::translate(glm::mat4(1.0f), transform.position);
            auto rotationMatrix = glm::toMat4(glm::quat(transform.rotation));
            auto scaleMatrix = glm::scale(glm::mat4(1.0f), transform.scale);

            auto modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

            if (meshRenderer.useTxtures)
            {
                Renderer::Renderer3D::Submit(model, modelMatrix, meshRenderer.albedoTexture->GetTexture(), meshRenderer.metallicTexture->GetTexture(),
                                             meshRenderer.roughnessTexture->GetTexture(), meshRenderer.aoTexture->GetTexture());
            }
            else
            {
                Renderer::Renderer3D::Submit(model, modelMatrix, meshRenderer.albedo, meshRenderer.metallic,
                                             meshRenderer.roughness, meshRenderer.ao);
            }
        });

    Renderer::Renderer3D::End();
}

void Scene::OnShutdown()
{
    Log::LogInfo("OnShutdown Scene: " + name);
}

Entity Scene::CreateEntity(std::string tag)
{
    auto entityHandle = ecsWorld.entity();

    Entity entity = {entityHandle, this};
    entity.AddComponent<Tag>(tag);

    return entity;
}

Entity Scene::GetEntityByTag(std::string tag)
{
    if (auto e = ecsWorld.entity(tag.c_str()); e.is_alive())
        return {e, this};
    return {};
}

std::vector<Entity> Scene::GetAllEntities()
{
    std::vector<Entity> entities;

    flecs::filter f = ecsWorld.filter<Tag>();
    f.each([&](flecs::entity e, Tag& tag) { entities.push_back({e, this}); });
    return entities;
}
} // namespace SignE::Core::Scene
