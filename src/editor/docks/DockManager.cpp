#include "rayeditor.hpp"

using namespace RayEditor::Docks;

/// <summary>
/// Draws and handles docks/menus UI.
/// </summary>
void DockManager::UpdateDocks() {
    int index = 0;
    for (Dock& dock : activeDocks)
    {
        index++;
        if (!dock.isInitialized)
        {
            windowsOpen++;
            dock.StartWindow();
            dock.isInitialized = true;
        }

        dock.DrawWindow(index);
    }
}

// <summary>
// Unitialize all docks and close them.
// </summary>
void DockManager::CloseDocks() {
    for (Dock& dock : activeDocks) dock.CloseWindow();
}