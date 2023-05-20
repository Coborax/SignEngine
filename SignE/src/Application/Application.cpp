//
// Created by Mikkel Mouridsen on 17/12/2022.
//
#include <iostream>

#include "Application/ApplicationLayer.h"
#include "Application/Window.h"
#include "Renderer/Renderer2D.h"
#include "Scripting/LuaScriptEngine.h"
#include "Application.h"
#include "Log.h"
#include "Ref.h"
#include "Renderer/Renderer.h"

namespace SignE::Core::Application {
    using namespace SignE::Core::Scripting;

    Ref<Window> Application::window = nullptr;

    float Application::GetDeltaTime() {
        return 0.0f;
    }

    Ref<Window> Application::GetWindow() {
        return window;
    }

    void Application::Run() {

        Renderer::RenderCommand::Create(Renderer::RenderAPI::OpenGL);

        Log::LogInfo("Initializing Window");
        window = CreateRef<Window>(name, 1280, 720);


        Log::LogInfo("Initializing Renderer");
        Renderer::RenderCommand::Init();
        Renderer::RenderCommand::SetClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        Renderer::Renderer2D::Init();

        Log::LogInfo("Initializing Lua Scripting Engine");
        LuaScriptEngine::Init();

        for (ApplicationLayer* layer: layers) {
            layer->OnInit();
        }

        running = true;
        while (!window->ShouldClose()) {
            Renderer::RenderCommand::Clear();
            window->PollEvents(); 

            // Update application layers
            for (ApplicationLayer* layer: layers) {
                layer->OnUpdate(GetDeltaTime());
            }

            // Draw application layers
            for (ApplicationLayer* layer: layers) {
                layer->OnDraw();
            }

            window->SwapBuffers();
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

