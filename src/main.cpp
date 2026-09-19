#include <raylib.h>
#include <iostream>
#include <imgui.h>
#include <rlImGui.h>
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

#pragma region imgui
    rlImGuiSetup(true);
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.FontGlobalScale = 2.5;
#pragma endregion
    if (!initGame()) {
        return 0;
    }

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
#pragma region imgui
        rlImGuiBegin();
#pragma endregion
#pragma region imgui
        ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
        ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
        ImGuiID dockId = ImGui::GetID("MainDockSpace");
        ImGui::DockSpaceOverViewport(dockId, ImGui::GetMainViewport());
        ImGui::PopStyleColor(2);
#pragma endregion
        if (!updateGame())
        {
            CloseWindow();
        }
#pragma region imgui
        rlImGuiEnd();
#pragma endregion
        EndDrawing(); 
    }
#pragma region imgui
    rlImGuiShutdown();
#pragma endregion
    CloseWindow();
    closeGame();

#pragma region imgui
    rlImGuiShutdown();
#pragma endregion
    return 0;
}