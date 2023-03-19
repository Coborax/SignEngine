//
// Created by Mikkel Mouridsen on 18/12/2022.
//

#ifndef SIGNEPROJECT_RENDERER2D_H
#define SIGNEPROJECT_RENDERER2D_H

#include "raylib.h"
namespace SignE::Core::Renderer{
    class Renderer2D {
    public:
        /**
         * Start batch rendering
         */
        static void BeginDraw();
        static void EndDraw();

        static void InitRenderTexture();
        static void BeginDrawRenderTexture();
        static void EndDrawRenderTexture();
        static void CleanupRenderTexture();

        static void DrawRect(int posX, int posY, int width, int height);
        static void DrawRect(int posX, int posY, int width, int height, float r, float g, float b, float a);

        static void BeginImGui();
        static void EndImGui();
        static void CleanupImGui();

        static void ImGuiDrawRenderTexture(int width, int height);

        static void DrawFPS();

    private:
        static RenderTexture renderTexture;
    };
}

#endif //SIGNEPROJECT_RENDERER2D_H
