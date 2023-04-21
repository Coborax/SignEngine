//
// Created by Mikkel Mouridsen on 13/01/2023.
//

#include <string>
namespace SignE::Core::Scene::Components {
    struct Position {
        float x;
        float y;
    };

    struct Rect {
        float width;
        float height;
    };

    struct Color {
        float r = 1;
        float g = 1;
        float b = 1;
        float a = 1;
    };

    struct RectangleRenderer {
        Rect& rect;
        Color color;
    };

    struct LuaScript {
        std::string code;
    };

}
