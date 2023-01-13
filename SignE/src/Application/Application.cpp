//
// Created by Mikkel Mouridsen on 17/12/2022.
//
#include <iostream>

#include "raylib.h"

#include "Application.h"
#include "Log.h"

void Application::Run() {

    Log::LogInfo("Initializing Window");
    InitWindow(1280, 720, name.c_str());

    for (ApplicationLayer* layer: layers) {
        layer->OnInit();
    }

    running = true;
    while (!WindowShouldClose()) {
        // Update application layers
        for (ApplicationLayer* layer: layers) {
            layer->OnUpdate(GetFrameTime());
        }

        // Draw application layers
        for (ApplicationLayer* layer: layers) {
            layer->OnDraw();
        }
    }

    Log::LogInfo("Application Shutting Down");

    running = false;

    for (ApplicationLayer* layer: layers) {
        layer->OnShutdown();
    }
}

void Application::PushLayer(ApplicationLayer* layer) {
    layers.push_back(layer);

    // If we push a layer while the game is running we want to initialize it
    if (running) {
        layer->OnInit();
    }
}
