#include <rlImGui.h>
#include "rayeditor.hpp"
#include <iostream>

using namespace RayEditor;

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

    // Argument 0 is the application name
    if (argc > 1)
    {
        if (!Project::SetProjectDirectory(argv[1])) // Argument one is a project directory to open
        {
            Log::Warning("Project could not be loaded check that this is a valid project directory with a project.ray file.");
        }
        else
        {
            Log::Info("Project loaded: " + std::string(Project::GetProjectDirectory()));
        }
    }

    bool dockspaceActive;

    //Create base docks
    Docks::AssetDock assetDock;

    // Make base docks active
    Docks::DockManager::activeDocks.push_back(assetDock);

    Log::Info("Welcome to " + Title); // Greetings!

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

            Docks::ToolbarDock::DrawWindow(); // The top toolbar of the editor is made before dockspace starts so it can't be docked.

            ImGui::End(); // Dockspace starts here.

            Docks::ConsoleDock::DrawWindow(); // Console dock is static and always visible.

            if (dockspaceActive) Docks::DockManager::UpdateDocks(); // Regular docks/tools.

        rlImGuiEnd();

            DrawFPS(0, GetScreenHeight() - 20);

        EndDrawing();
    }

    // |De-Initialization|
    //--------------------------------

    Docks::DockManager::CloseDocks();
    rlImGuiShutdown();
    CloseWindow();
    //--------------------------------

    return 0;
}