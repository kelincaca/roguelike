#include <raylib.h>
#include <iostream>
#include <gameMain.h>

int main(void)
{
#if PRODUCTION_BUILD==1
    SetTraceLogLevel(LOG_NONE);
#endif
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 450, "window name");
    SetExitKey(KEY_NULL);
    SetTargetFPS(240);

    if (!initGame()) {
        return 0;
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        if (!updateGame())
        {
            CloseWindow();
        }
        EndDrawing();
    }
    CloseWindow();
    closeGame();

    return 0;
}