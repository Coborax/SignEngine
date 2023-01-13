//
// Created by Mikkel Mouridsen on 18/12/2022.
//

#include "raylib.h"

#include "Renderer2D.h"
#include "rlImGui.h"
#include "imgui.h"

void Renderer2D::BeginDraw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
}

void Renderer2D::EndDraw() {
    EndDrawing();
}

void Renderer2D::DrawRect(int posX, int posY) {
    DrawRectangle(posX, posY, 100, 100, BLUE);
}

void Renderer2D::BeginImGui() {
    rlImGuiBegin();
}

void Renderer2D::EndImGui() {
    rlImGuiEnd();
}

void Renderer2D::CleanupImGui() {
    rlImGuiShutdown();
}

void Renderer2D::InitRenderTexture() {
    renderTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
}

void Renderer2D::CleanupRenderTexture() {
    UnloadRenderTexture(renderTexture);
}

void Renderer2D::BeginDrawRenderTexture() {
    BeginTextureMode(renderTexture);
    ClearBackground(RAYWHITE);
}

void Renderer2D::EndDrawRenderTexture() {
    EndTextureMode();
}

void Renderer2D::ImGuiDrawRenderTexture(int width, int height) {
    Rectangle viewRect = { 0 };
    viewRect.x = renderTexture.texture.width / 2 - width / 2;
    viewRect.y = renderTexture.texture.height / 2 - height / 2;
    viewRect.width = width;
    viewRect.height = -height;

    rlImGuiImageRect(&renderTexture.texture, (int)width, (int)height, viewRect);
}

RenderTexture Renderer2D::renderTexture;