#include <rlImGui.h>
#include "rayeditor.hpp"
#include <iostream>

using namespace RayEditor;
using namespace Utility;
using namespace Docks;
using namespace Editor;

int main(int argc, char *argv[]){
    int screenWidth = 1280;
    int screenHeight = 800;
    const std::string Title("RayEditor V" + std::string(EDITOR_VERSION));

    // Some basic setup stuff
    SetTraceLogCallback(Log::TraceLog);
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, Title.c_str());
    SetWindowMinSize(screenWidth, screenHeight);
    rlImGuiSetup(true);

    // First argument is a directory path to a possible project.
    if (argc > 1)
    {
        if (!Project::SetProjectDirectory(argv[1]))
        {
            Log::Warning("Project could not be loaded check that this is a valid project directory with a project.ray file.");
        }
        else
        {
            Log::Info("Project loaded: " + std::string(Project::GetProjectDirectory()));
        }
    }

    Log::Info("Welcome to " + Title); // Greetings!

    bool dockspaceActive;

    while (!WindowShouldClose() && !Application::quit)
    {

        BeginDrawing();

            ClearBackground(DARKBLUE);

        rlImGuiBegin();

            // Main Dockspace
            //_________________________________________________________________________________________________________________________________________________________________
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(float(GetScreenWidth()), float(GetScreenHeight())));

            ImGuiWindowFlags dockSpaceFlags = ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar
            | ImGuiWindowFlags_NoResize |ImGuiWindowFlags_NoMove |ImGuiWindowFlags_NoCollapse |ImGuiWindowFlags_MenuBar |ImGuiWindowFlags_NoBackground;
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

            dockspaceActive = (ImGui::Begin("Main", NULL, dockSpaceFlags));
            ImGui::PopStyleVar();

            ImGui::DockSpace(ImGui::GetID("Dockspace"), ImVec2(0.0f, 0.0f),  ImGuiDockNodeFlags_PassthruCentralNode);
            //_________________________________________________________________________________________________________________________________________________________________

            ToolbarDock::DrawWindow();

            ImGui::End();

            if (dockspaceActive) DockManager::DrawDocks();

        rlImGuiEnd();

            DrawFPS(0, GetScreenHeight() - 20);

        EndDrawing();
    }

    // |De-Initialization|
    //--------------------

    rlImGuiShutdown();
    CloseWindow();

    return 0;
}