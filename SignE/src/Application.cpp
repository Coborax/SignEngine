//
// Created by Mikkel Mouridsen on 17/12/2022.
//
#include <iostream>

#include "Application.h"
#include "raylib.h"

void Application::Run() {

    InitWindow(1920, 1080, "SignE");

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }
}