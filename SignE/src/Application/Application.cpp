//
// Created by Mikkel Mouridsen on 17/12/2022.
//
#include <iostream>

#include "raylib.h"

#include "Application.h"
#include "Log.h"

void Application::Run() {

    Log::LogInfo("Initializing Window");
    InitWindow(1280, 720, "SignE");

    while (!WindowShouldClose()) {
        // Update application layers
        for (ApplicationLayer* layer: layers) {
            layer->Update(GetFrameTime());
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw application layers
        for (ApplicationLayer* layer: layers) {
            layer->Draw();
        }

        EndDrawing();
    }

    Log::LogInfo("Application Shutting Down");
}