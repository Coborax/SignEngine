//
// Created by Mikkel Mouridsen on 18/12/2022.
//

#include "raylib.h"

#include "Renderer2D.h"
#include "rlImGui.h"

namespace SignE::Core::Renderer {
void Renderer2D::BeginDraw() {
  BeginDrawing();
  ClearBackground(RAYWHITE);
}

void Renderer2D::EndDraw() { EndDrawing(); }

void Renderer2D::DrawRect(int posX, int posY, int width, int height) {
  DrawRectangle(posX, posY, width, height, BLUE);
}

void Renderer2D::DrawRect(int posX, int posY, int width, int height, float r,
                          float g, float b, float a) {
  DrawRectangle(posX, posY, width, height, ColorFromNormalized({r, g, b, a}));
}

void Renderer2D::BeginImGui() { rlImGuiBegin(); }

void Renderer2D::EndImGui() { rlImGuiEnd(); }

void Renderer2D::CleanupImGui() { rlImGuiShutdown(); }

void Renderer2D::InitRenderTexture() {
  renderTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
}

void Renderer2D::CleanupRenderTexture() { UnloadRenderTexture(renderTexture); }

void Renderer2D::BeginDrawRenderTexture() {
  BeginTextureMode(renderTexture);
  ClearBackground(RAYWHITE);
}

void Renderer2D::EndDrawRenderTexture() { EndTextureMode(); }

void Renderer2D::ImGuiDrawRenderTexture(int width, int height) {
  Rectangle viewRect = {0};
  viewRect.x = 0;
  viewRect.y = 0;
  viewRect.width = width;
  viewRect.height = -height;

  rlImGuiImageRect(&renderTexture.texture, (int)width, (int)height, viewRect);
}

void Renderer2D::DrawFPS() { ::DrawFPS(10, 10); }

RenderTexture Renderer2D::renderTexture;
} // namespace SignE::Core::Renderer
