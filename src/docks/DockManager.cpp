#include "rayeditor.hpp"

using namespace RayEditor;
using namespace Docks;
using namespace Editor;

/// <summary>
/// Draws and handles docks/menus UI.
/// </summary>
void DockManager::DrawDocks() {
    ConsoleDock::DrawWindow();

    if (Project::IsProjectLoaded)
    {
        AssetDock::DrawWindow();
    }
}

void DockManager::CloseDocks() {
    AssetDock::CloseWindow();
}