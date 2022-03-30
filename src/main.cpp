#include <rlImGui.h>
#include "rayeditor.hpp"

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

    while (!WindowShouldClose())
    {

        BeginDrawing();

            ClearBackground(DARKBLUE);

        rlImGuiBegin();

            DockManager::DrawDocks();

        rlImGuiEnd();
        EndDrawing();
    }

    // |De-Initialization|
    //--------------------

    rlImGuiShutdown();
    CloseWindow();

    return 0;
}