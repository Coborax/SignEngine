//
// Created by Mikkel Mouridsen on 18/12/2022.
//

#ifndef SIGNEPROJECT_RENDERER2D_H
#define SIGNEPROJECT_RENDERER2D_H

#include "raylib.h"

class Renderer2D {
public:
    static void BeginDraw();
    static void EndDraw();

    static void InitRenderTexture();
    static void BeginDrawRenderTexture();
    static void EndDrawRenderTexture();
    static void CleanupRenderTexture();

    static void DrawRect(int posX, int posY);

    static void BeginImGui();
    static void EndImGui();
    static void CleanupImGui();

    static void ImGuiDrawRenderTexture(int width, int height);

private:
    static RenderTexture renderTexture;
};


#endif //SIGNEPROJECT_RENDERER2D_H
