//
// Created by Mikkel Mouridsen on 17/12/2022.
//
#include <iostream>

#include "raylib.h"

#include "Application.h"
#include "Log.h"

void Application::Run() {

    Log::LogInfo("Initializing Window");
    InitWindow(1920, 1080, "SignE");

    while (!WindowShouldClose()) {
        for (ApplicationLayer* layer: layers) {
            layer->Update(GetFrameTime());
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    Log::LogInfo("Application Shutting Down");
}