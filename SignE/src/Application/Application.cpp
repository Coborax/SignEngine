//
// Created by Mikkel Mouridsen on 17/12/2022.
//
#include <iostream>

#include "Application/Window.h"
#include "Renderer/Renderer2D.h"
#include "Scripting/LuaScriptEngine.h"
#include "Application.h"
#include "Log.h"
#include "Renderer/Renderer.h"

namespace SignE::Core::Application {
    using namespace SignE::Core::Scripting;

    float Application::GetDeltaTime() {
        return 0.0f;
    }

    void Application::Run() {

        Log::LogInfo("Initializing Window");
        Window window("SignE", 1280, 720);

        Log::LogInfo("Initializing Renderer");
        Renderer::RenderCommand::Create(Renderer::RenderAPI::OpenGL);
        Renderer::RenderCommand::Init();

        Renderer::Renderer2D::Init();

        Log::LogInfo("Initializing Lua Scripting Engine");
        LuaScriptEngine::Init();

        for (ApplicationLayer* layer: layers) {
            layer->OnInit();
        }

        running = true;
        while (!window.ShouldClose()) {
            Renderer::RenderCommand::Clear();

            // Update application layers
            for (ApplicationLayer* layer: layers) {
                layer->OnUpdate(GetDeltaTime());
            }

            // Draw application layers
            for (ApplicationLayer* layer: layers) {
                layer->OnDraw();
            }

            window.SwapBuffers();
            window.PollEvents(); 
        }

        Log::LogInfo("Application Shutting Down");

        running = false;

        for (ApplicationLayer* layer: layers) {
            layer->OnShutdown();
        }

        Log::LogInfo("Shutting Down Lua Scripting Engine");
        LuaScriptEngine::Shutdown();
    }

    void Application::PushLayer(ApplicationLayer* layer) {
        layers.push_back(layer);

        // If we push a layer while the game is running we want to initialize it
        if (running) {
            layer->OnInit();
        }
    }
}

