//
// Created by Mikkel Mouridsen on 18/12/2022.
//

#ifndef SIGNEPROJECT_SCENE_H
#define SIGNEPROJECT_SCENE_H

#include <flecs/addons/cpp/mixins/rest/decl.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <utility>
#include <glm/glm.hpp>
#include <vector>
#include <flecs.h>

#include "Ref.h"
#include "Scene/SceneSerializer.h"
#include "../Log.h"
#include "Input/Input.h"
#include "Application/Application.h"
#include "Application/Window.h"

namespace SignE::Core::Scene
{
class Entity;

class Camera
{
public:
    Camera() = default;

    virtual glm::mat4 GetViewMatrix() const = 0;
    virtual glm::mat4 GetProjectionMatrix() const = 0;

    virtual glm::vec3 GetPosition() const = 0;
    virtual glm::vec3 GetRotation() const = 0;

    virtual void SetPosition(const glm::vec3& position) = 0;
    virtual void SetRotation(const glm::vec3& rotation) = 0;

    virtual void SetViewportSize(float width, float height) = 0;

    virtual void Update(float dt) = 0;
};

class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera() = default;
    PerspectiveCamera(float fov, float aspectRatio, float near, float far)
        : fov(fov), aspectRatio(aspectRatio), near(near), far(far){};

    glm::mat4 GetProjectionMatrix() const override
    {
        return glm::perspective(fov, aspectRatio, near, far);
    }

    void SetViewportSize(float width, float height) override
    {
        aspectRatio = width / height;
    }

private:
    float fov = 45.0f;
    float aspectRatio = 1280.0f / 720.0f;
    float near = 0.1f;
    float far = 100.0f;
};

class FPSCamera : public PerspectiveCamera
{
public:
    glm::mat4 GetViewMatrix() const override
    {
        return glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
    }

    void Update(float dt) override
    {
        auto deltaSpeed = cameraSpeed * dt;

        if (Input::Input::IsKeyPressed(Input::KeyCode::W))
            cameraPosition += deltaSpeed * cameraFront;
        if (Input::Input::IsKeyPressed(Input::KeyCode::S))
            cameraPosition -= deltaSpeed * cameraFront;
        if (Input::Input::IsKeyPressed(Input::KeyCode::A))
            cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * deltaSpeed;
        if (Input::Input::IsKeyPressed(Input::KeyCode::D))
            cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * deltaSpeed;

        if (Input::Input::IsKeyPressed(Input::KeyCode::Space))
            cameraPosition += deltaSpeed * cameraUp;
        if (Input::Input::IsKeyPressed(Input::KeyCode::LeftControl))
            cameraPosition -= deltaSpeed * cameraUp;

        if (Input::Input::IsKeyPressed(Input::KeyCode::LeftShift))
            cameraSpeed = 10.0f;
        else
            cameraSpeed = 5.0f;

        Application::Application::GetWindow()->SetCaptureMouse(Input::Input::IsMouseButtonPressed(1));
        if (!Input::Input::IsMouseButtonPressed(1))
            return;

        auto [mouseDeltaX, mouseDeltaY] = Input::Input::GetMouseDelta();
        yaw += mouseDeltaX * cameraSensitivity;
        pitch += mouseDeltaY * cameraSensitivity;

        if (pitch > 89.0f)
            pitch = 89.0f;

        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);
    }

    glm::vec3 GetPosition() const override
    {
        return cameraPosition;
    }

    glm::vec3 GetRotation() const override
    {
        return cameraFront;
    }

    void SetPosition(const glm::vec3& position) override
    {
        cameraPosition = position;
    }

    void SetRotation(const glm::vec3& rotation) override
    {
        cameraFront = rotation;
    }

private:
    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float cameraSpeed = 5.0f;
    float cameraSensitivity = 0.1f;

    float yaw = -90.0f;
    float pitch = 0.0f;
};

class Scene
{
public:
    Scene() : name("Scene"), camera(CreateRef<FPSCamera>()){};
    Scene(std::string name) : name(std::move(name)), camera(CreateRef<FPSCamera>()){};

    void OnInit();
    void OnUpdate(float dt);
    void OnDraw();
    void OnShutdown();

    Entity CreateEntity(std::string tag);
    Entity GetEntityByTag(std::string tag);
    std::vector<Entity> GetAllEntities();

    Ref<Camera> GetCamera() const
    {
        return camera;
    }

    friend class Entity;
    friend class SceneSerializer;

private:
    // entt::registry registry;
    flecs::world ecsWorld;

    Ref<Camera> camera;

    std::string name;
};
} // namespace SignE::Core::Scene

#endif // SIGNEPROJECT_SCENE_H
