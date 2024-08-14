#include <iostream>
#include <raylib.h>
#include <raymath.h>

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "dotlambda"

const int screenWidth = 800;
const int screenHeight = 450;

int main()
{
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
