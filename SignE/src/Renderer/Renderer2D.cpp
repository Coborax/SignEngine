//
// Created by Mikkel Mouridsen on 18/12/2022.
//

#include "Renderer2D.h"
#include "Log.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/Renderer.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <unordered_map>
#include <tiny_obj_loader.h>

namespace SignE::Core::Renderer
{

void Renderer2D::Init()
{
    Log::LogInfo("Initializing Renderer2D");
}

void Renderer2D::BeginDraw()
{}

void Renderer2D::EndDraw()
{}

void Renderer2D::DrawRect(int posX, int posY, int width, int height)
{
    DrawRect(posX, posY, width, height, 1.0f, 1.0f, 1.0f, 1.0f);
}

void Renderer2D::DrawRect(int posX, int posY, int width, int height, float r, float g, float b, float a)
{
}

void Renderer2D::BeginImGui()
{}

void Renderer2D::EndImGui()
{}

void Renderer2D::CleanupImGui()
{}

void Renderer2D::InitRenderTexture()
{}

void Renderer2D::CleanupRenderTexture()
{}

void Renderer2D::BeginDrawRenderTexture()
{}

void Renderer2D::EndDrawRenderTexture()
{}

void Renderer2D::ImGuiDrawRenderTexture(int width, int height)
{}

void Renderer2D::DrawFPS()
{}

} // namespace SignE::Core::Renderer
