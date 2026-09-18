#include "raylib.h"

int main()
{
    InitWindow(800, 450, "Raylib test");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("成功跑通raylib！",100,100,30,BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
