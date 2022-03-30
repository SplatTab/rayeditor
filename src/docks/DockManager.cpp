#include "rayeditor.hpp"

using namespace RayEditor;
using namespace Docks;
using namespace Editor;

/// <summary>
/// Draws and handles docks/menus UI.
/// </summary>
void DockManager::DrawDocks() {
    TopMenuDock::DrawWindow();
    ConsoleDock::DrawWindow();

    if (Project::IsProjectLoaded())
    {
        AssetDock::DrawWindow();
    }
}