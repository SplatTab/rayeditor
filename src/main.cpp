#include <rlImGui.h>
#include "rayeditor.hpp"

using namespace RayEditor;
using namespace Utility;
using namespace Docks;

int main(int argc, char* argv[])
{
	int screenWidth = 1280;
	int screenHeight = 800;

	SetTraceLogCallback(Log::TraceLog);
	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "RayEditor V0.0.1");
	rlImGuiSetup(true);
	
	Log::Info("Welcome to RayEditor V0.0.1");

	while (!WindowShouldClose())
	{

		BeginDrawing();
		ClearBackground(DARKGRAY);

        rlImGuiBegin();
        
            DrawText("This is in the game", 20, 20, 20, BLACK);

            DockManager::DrawDocks();

		rlImGuiEnd();
		EndDrawing();
	}

	rlImGuiShutdown();
	CloseWindow();

	return 0;
}