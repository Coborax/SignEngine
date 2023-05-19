#include "SceneSerializer.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <yaml-cpp/yaml.h>

#include "Scene.h"
#include "Entity.h"
#include "Scene/Components.h"

namespace SignE::Core::Scene {
    void SceneSerializer::Deserialize(const std::string& filepath) {
        YAML::Emitter out;
        
        out << YAML::BeginMap;

        out << YAML::Key << "Scene";
        out << YAML::Value << scene->name;

        out << YAML::Key << "Entities";
        out << YAML::Value << YAML::BeginSeq;
        for (auto entity : scene->GetAllEntities()) {
            out << YAML::BeginMap;

            out << YAML::Key << entity.GetTag();
            out << YAML::Value << YAML::BeginMap;

            out << YAML::Key << "Components";
            out << YAML::Value << YAML::BeginMap;

            if (entity.HasComponent<Tag>()) {
                out << YAML::Key << "Tag";
                out << YAML::Value << entity.GetComponent<Tag>().tag;
            }

            if (entity.HasComponent<Position>()) {
                out << YAML::Key << "Position";
                out << YAML::Value << YAML::BeginMap;

                out << YAML::Key << "X";
                out << YAML::Value << entity.GetComponent<Position>().x;
                out << YAML::Key << "Y";
                out << YAML::Value << entity.GetComponent<Position>().y;

                out << YAML::EndMap;
            }

            if (entity.HasComponent<Rect>()) {
                out << YAML::Key << "Rect";
                out << YAML::Value << YAML::BeginMap;

                out << YAML::Key << "Width";
                out << YAML::Value << entity.GetComponent<Rect>().width;
                out << YAML::Key << "Height";
                out << YAML::Value << entity.GetComponent<Rect>().height;

                out << YAML::EndMap;
            }

            if (entity.HasComponent<RectangleRenderer>()) {
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

            if (entity.HasComponent<LuaScript>()) {
                out << YAML::Key << "LuaScript";
                out << YAML::Value << YAML::BeginMap;

                out << YAML::Key << "Code";
                out << YAML::Value << entity.GetComponent<LuaScript>().code;

                out << YAML::EndMap;
            }

            out << YAML::EndMap;

            out << YAML::EndMap;
            
            out << YAML::EndMap;
        }
        out << YAML::EndSeq;

        out << YAML::EndMap;
        
        std::filesystem::path path(filepath);
        std::ofstream ofs(filepath);
        ofs << out.c_str();
        ofs.close();
    }

    void SceneSerializer::Serialize(const std::string& filepath) {
        YAML::Node config = YAML::LoadFile(filepath);

        scene->name = config["Scene"].as<std::string>();

        auto entities = config["Entities"];
        for (auto entity : entities) {
            auto tag = entity.begin()->first.as<std::string>();
            auto components = entity.begin()->second["Components"];
            auto newEntity = scene->CreateEntity(tag);

            if (components["Tag"]) {
                newEntity.AddComponent<Tag>(components["Tag"].as<std::string>());
            }
            if (components["Position"]) {
                auto position = components["Position"];
                newEntity.AddComponent<Position>(position["X"].as<float>(), position["Y"].as<float>());
            }
            if (components["Rect"]) {
                auto rect = components["Rect"];
                newEntity.AddComponent<Rect>(rect["Width"].as<float>(), rect["Height"].as<float>());
            }
            if (components["RectangleRenderer"]) {
                auto rectangleRenderer = components["RectangleRenderer"];
                auto rect = rectangleRenderer["Rect"];
                auto color = rectangleRenderer["Color"];
                newEntity.AddComponent<RectangleRenderer>(Rect{ rect["Width"].as<float>(), rect["Height"].as<float>() }, Color{color["R"].as<float>(), color["G"].as<float>(), color["B"].as<float>(), color["A"].as<float>()});
            }
            if (components["LuaScript"]) {
                auto luaScript = components["LuaScript"];
                newEntity.AddComponent<LuaScript>(luaScript["Code"].as<std::string>());
            }
        }
    }
}
