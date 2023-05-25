//
// Created by Mikkel Mouridsen on 13/01/2023.
//

#ifndef SIGNEPROJECT_COMPONENTS_H
#define SIGNEPROJECT_COMPONENTS_H

#include "Ref.h"

#include <glm/glm.hpp>
#include <string>

namespace SignE::Core
{
class Model;
namespace Renderer
{
    class Texture;
}
} // namespace SignE::Core

namespace SignE::Core::Scene::Components
{

struct Tag
{
    std::string tag;

    Tag()
    {}

    Tag(const std::string& tag) : tag(tag)
    {}
};

struct Position
{
    float x;
    float y;

    Position()
    {}

    Position(float x, float y) : x(x), y(y)
    {}
};

struct Rect
{
    float width;
    float height;

    Rect()
    {}

    Rect(float width, float height) : width(width), height(height)
    {}
};

struct Color
{
    float r = 1;
    float g = 1;
    float b = 1;
    float a = 1;

    Color()
    {}

    Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
    {}
};

struct RectangleRenderer
{
    Rect rect;
    Color color;

    RectangleRenderer(const Rect& rect, const Color& color) : rect(rect), color(color)
    {}
};

struct LuaScript
{
    std::string code;

    LuaScript()
    {}

    LuaScript(const std::string& code) : code(code)
    {}
};

// 3D
struct Transform
{
    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::vec3 rotation = glm::vec3(0, 0, 0);
    glm::vec3 scale = glm::vec3(1, 1, 1);

    Transform()
    {}

    Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
        : position(position), rotation(rotation), scale(scale)
    {}
};

struct MeshRenderer
{
    std::string modelPath;
    std::string texturePath;

    MeshRenderer()
    {}

    MeshRenderer(const std::string& modelPath, const std::string& texturePath)
        : modelPath(modelPath), texturePath(texturePath)
    {}
};

} // namespace SignE::Core::Scene::Components

#endif // SIGNEPROJECT_COMPONENTS_H
