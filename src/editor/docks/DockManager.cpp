#include "rayeditor.hpp"

using namespace RayEditor::Docks;

int windowsOpen;

/// <summary>
/// Draws and handles docks/menus UI.
/// </summary>
void DockManager::UpdateDocks() {
    for (Dock& dock : activeDocks)
    {
        if (!dock.isInitialized)
        {
            windowsOpen++;
            dock.id = windowsOpen;
            dock.StartWindow();
            dock.isInitialized = true;
        }

        dock.DrawWindow();
    }
}

// <summary>
// Unitialize all docks and close them.
// </summary>
void DockManager::CloseDocks() {
    for (Dock& dock : activeDocks) dock.CloseWindow();
}