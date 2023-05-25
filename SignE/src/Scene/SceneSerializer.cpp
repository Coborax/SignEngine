#include "SceneSerializer.h"

#include "Scene.h"
#include "Entity.h"
#include "Scene/Components.h"
#include "FileSystem/VirtualFileSystem.h"

#include <glm/fwd.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <yaml-cpp/yaml.h>

namespace SignE::Core::Scene
{
void SceneSerializer::Deserialize(const std::string& filepath)
{
    YAML::Emitter out;

    out << YAML::BeginMap;

    out << YAML::Key << "Scene";
    out << YAML::Value << scene->name;

    out << YAML::Key << "EditorCamera";
    out << YAML::Value << YAML::BeginMap;

    out << YAML::Key << "Position";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "X";
    out << YAML::Value << scene->camera->GetPosition().x;
    out << YAML::Key << "Y";
    out << YAML::Value << scene->camera->GetPosition().y;
    out << YAML::Key << "Z";
    out << YAML::Value << scene->camera->GetPosition().z;
    out << YAML::EndMap;

    out << YAML::Key << "Rotation";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "X";
    out << YAML::Value << scene->camera->GetRotation().x;
    out << YAML::Key << "Y";
    out << YAML::Value << scene->camera->GetRotation().y;
    out << YAML::Key << "Z";
    out << YAML::Value << scene->camera->GetRotation().z;
    out << YAML::EndMap;

    out << YAML::EndMap;

    out << YAML::Key << "Entities";
    out << YAML::Value << YAML::BeginSeq;
    for (auto entity : scene->GetAllEntities())
    {
        out << YAML::BeginMap;

        out << YAML::Key << entity.GetTag();
        out << YAML::Value << YAML::BeginMap;

        out << YAML::Key << "Components";
        out << YAML::Value << YAML::BeginMap;

        if (entity.HasComponent<Tag>())
        {
            out << YAML::Key << "Tag";
            out << YAML::Value << entity.GetComponent<Tag>().tag;
        }

        if (entity.HasComponent<Position>())
        {
            out << YAML::Key << "Position";
            out << YAML::Value << YAML::BeginMap;

            out << YAML::Key << "X";
            out << YAML::Value << entity.GetComponent<Position>().x;
            out << YAML::Key << "Y";
            out << YAML::Value << entity.GetComponent<Position>().y;

            out << YAML::EndMap;
        }

        if (entity.HasComponent<Rect>())
        {
            out << YAML::Key << "Rect";
            out << YAML::Value << YAML::BeginMap;

            out << YAML::Key << "Width";
            out << YAML::Value << entity.GetComponent<Rect>().width;
            out << YAML::Key << "Height";
            out << YAML::Value << entity.GetComponent<Rect>().height;

            out << YAML::EndMap;
        }

        if (entity.HasComponent<RectangleRenderer>())
        {
            out << YAML::Key << "RectangleRenderer";
            out << YAML::Value << YAML::BeginMap;

            out << YAML::Key << "Rect";
            out << YAML::Value << YAML::BeginMap;

            out << YAML::Key << "Width";
            out << YAML::Value << entity.GetComponent<Rect>().width;
            out << YAML::Key << "Height";
            out << YAML::Value << entity.GetComponent<Rect>().height;

            out << YAML::EndMap;

            out << YAML::Key << "Color";
            out << YAML::Value << YAML::BeginMap;

            out << YAML::Key << "R";
            out << YAML::Value << entity.GetComponent<RectangleRenderer>().color.r;
            out << YAML::Key << "G";
            out << YAML::Value << entity.GetComponent<RectangleRenderer>().color.g;
            out << YAML::Key << "B";
            out << YAML::Value << entity.GetComponent<RectangleRenderer>().color.b;
            out << YAML::Key << "A";
            out << YAML::Value << entity.GetComponent<RectangleRenderer>().color.a;

            out << YAML::EndMap;

            out << YAML::EndMap;
        }

        if (entity.HasComponent<LuaScript>())
        {
            out << YAML::Key << "LuaScript";
            out << YAML::Value << YAML::BeginMap;

            out << YAML::Key << "Code";
            out << YAML::Value << entity.GetComponent<LuaScript>().code;

            out << YAML::EndMap;
        }

        // 3D Components
        if (entity.HasComponent<Transform>())
        {
            out << YAML::Key << "Transform";
            out << YAML::Value << YAML::BeginMap;

            out << YAML::Key << "Position";
            out << YAML::Value << YAML::BeginMap;
            out << YAML::Key << "X";
            out << YAML::Value << entity.GetComponent<Transform>().position.x;
            out << YAML::Key << "Y";
            out << YAML::Value << entity.GetComponent<Transform>().position.y;
            out << YAML::Key << "Z";
            out << YAML::Value << entity.GetComponent<Transform>().position.z;
            out << YAML::EndMap;

            out << YAML::Key << "Rotation";
            out << YAML::Value << YAML::BeginMap;
            out << YAML::Key << "X";
            out << YAML::Value << entity.GetComponent<Transform>().rotation.x;
            out << YAML::Key << "Y";
            out << YAML::Value << entity.GetComponent<Transform>().rotation.y;
            out << YAML::Key << "Z";
            out << YAML::Value << entity.GetComponent<Transform>().rotation.z;
            out << YAML::EndMap;

            out << YAML::Key << "Scale";
            out << YAML::Value << YAML::BeginMap;
            out << YAML::Key << "X";
            out << YAML::Value << entity.GetComponent<Transform>().scale.x;
            out << YAML::Key << "Y";
            out << YAML::Value << entity.GetComponent<Transform>().scale.y;
            out << YAML::Key << "Z";
            out << YAML::Value << entity.GetComponent<Transform>().scale.z;
            out << YAML::EndMap;

            out << YAML::EndMap;
        }

        if (entity.HasComponent<MeshRenderer>())
        {
            out << YAML::Key << "MeshRenderer";
            out << YAML::Value << YAML::BeginMap;

            out << YAML::Key << "ModelPath";
            out << YAML::Value << entity.GetComponent<MeshRenderer>().modelPath;

            out << YAML::Key << "TexturePath";
            out << YAML::Value << entity.GetComponent<MeshRenderer>().texturePath;

            out << YAML::EndMap;
        }

        out << YAML::EndMap;

        out << YAML::EndMap;

        out << YAML::EndMap;
    }
    out << YAML::EndSeq;

    out << YAML::EndMap;

    auto absolutePath = VFS::Instance().GetAbsolutePath(filepath);
    std::filesystem::path path(absolutePath);
    std::ofstream ofs(absolutePath);
    ofs << out.c_str();
    ofs.close();
}

void SceneSerializer::Serialize(const std::string& filepath)
{
    auto absolutePath = VFS::Instance().GetAbsolutePath(filepath);
    YAML::Node config = YAML::LoadFile(absolutePath);

    scene->name = config["Scene"].as<std::string>();

    glm::vec3 cameraPosition = glm::vec3(config["EditorCamera"]["Position"]["X"].as<float>(), config["EditorCamera"]["Position"]["Y"].as<float>(), config["EditorCamera"]["Position"]["Z"].as<float>());
    glm::vec3 cameraRotation = glm::vec3(config["EditorCamera"]["Rotation"]["X"].as<float>(), config["EditorCamera"]["Rotation"]["Y"].as<float>(), config["EditorCamera"]["Rotation"]["Z"].as<float>());

    scene->camera->SetPosition(cameraPosition);
    scene->camera->SetRotation(cameraRotation);

    auto entities = config["Entities"];
    for (auto entity : entities)
    {
        auto tag = entity.begin()->first.as<std::string>();
        auto components = entity.begin()->second["Components"];
        auto newEntity = scene->CreateEntity(tag);

        // if (components["Tag"]) {
        //     newEntity.AddComponent<Tag>(components["Tag"].as<std::string>());
        // }
        if (components["Position"])
        {
            auto position = components["Position"];
            newEntity.AddComponent<Position>(position["X"].as<float>(), position["Y"].as<float>());
        }
        if (components["Rect"])
        {
            auto rect = components["Rect"];
            newEntity.AddComponent<Rect>(rect["Width"].as<float>(), rect["Height"].as<float>());
        }
        if (components["RectangleRenderer"])
        {
            auto rectangleRenderer = components["RectangleRenderer"];
            auto rect = rectangleRenderer["Rect"];
            auto color = rectangleRenderer["Color"];
            newEntity.AddComponent<RectangleRenderer>(
                Rect{rect["Width"].as<float>(), rect["Height"].as<float>()},
                Color{color["R"].as<float>(), color["G"].as<float>(), color["B"].as<float>(), color["A"].as<float>()});
        }
        if (components["LuaScript"])
        {
            auto luaScript = components["LuaScript"];
            newEntity.AddComponent<LuaScript>(luaScript["Code"].as<std::string>());
        }
        // 3D Components
        if (components["Transform"])
        {
            auto transform = components["Transform"];
            auto position = transform["Position"];
            auto rotation = transform["Rotation"];
            auto scale = transform["Scale"];
            newEntity.AddComponent<Transform>(
                glm::vec3{position["X"].as<float>(), position["Y"].as<float>(), position["Z"].as<float>()},
                glm::vec3{rotation["X"].as<float>(), rotation["Y"].as<float>(), rotation["Z"].as<float>()},
                glm::vec3{scale["X"].as<float>(), scale["Y"].as<float>(), scale["Z"].as<float>()});
        }

        if (components["MeshRenderer"])
        {
            auto meshRenderer = components["MeshRenderer"];
            newEntity.AddComponent<MeshRenderer>(meshRenderer["ModelPath"].as<std::string>(),
                                                 meshRenderer["TexturePath"].as<std::string>());
        }
    }
}
} // namespace SignE::Core::Scene
