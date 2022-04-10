#include "rayeditor.hpp"
#include <raypatcher.h>
#include <rlImGui.h>

using namespace RayEditor;

int main(int argc, char *argv[])
{
    int screenWidth = 1280;
    int screenHeight = 800;
    const std::string Title("RayEditor V" + std::string(EDITOR_VERSION));
    bool dockspaceActive;

    SetTraceLogCallback(Log::TraceLog);
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, Title.c_str());
    SetWindowMinSize(screenWidth, screenHeight);
    rlImGuiSetup(true);

    // Arg 0: Application name, Arg 1: Project directory
    if (argc > 1)
    {
        if (!Project::SetProjectDirectory(argv[1])) Log::Warning("Project could not be loaded check that this is a valid project directory with a project.ray file.");
        else Log::Info("Project loaded: " + std::string(Project::GetProjectDirectory()));
    }

    Docks::DockManager::activeDocks.push_back(std::make_unique<Docks::AssetManager>());
    Docks::DockManager::activeDocks.push_back(std::make_unique<Docks::SceneView>());

    CachedIcons::LoadIcons();

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

            // NOTE: The top toolbar is made before dockspace finishes drawing so it can't be docked.
            Docks::ToolbarMenu::DrawWindow();

            ImGui::End();

            // NOTE: Console Dock isn't made via DockManager 1: Do you really need two consoles 2: Logs would need to be sent to every console.
            Docks::Console::DrawWindow();

            if (dockspaceActive) Docks::DockManager::UpdateDocks();

        rlImGuiEnd();

            DrawFPS(GetScreenWidth() - 100, 20);

        EndDrawing();

        if (RPatcher::Update()) Application::recompiling = true;
        else Application::recompiling = false;

    }

    // |De-Initialization|
    //--------------------------------

    Docks::DockManager::CloseDocks();
    CachedIcons::UnloadIcons();
    rlImGuiShutdown();
    CloseWindow();
    //--------------------------------

    return 0;
}