//
// Created by Mikkel Mouridsen on 13/01/2023.
//

namespace SignE::Core::Scene {
    struct Position {
        float x;
        float y;
    };

    struct ColorRGBA {
        float r = 1;
        float g = 1;
        float b = 1;
        float a = 1;
    };

    struct RectangleRenderer {
        float width;
        float height;
        ColorRGBA color;
    };
}