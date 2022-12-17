//
// Created by Mikkel Mouridsen on 18/12/2022.
//

#include "raylib.h"

#include "Renderer2D.h"

void Renderer2D::DrawRect(int posX, int posY) {
    DrawRectangle(posX, posY, 100, 100, BLUE);
}
