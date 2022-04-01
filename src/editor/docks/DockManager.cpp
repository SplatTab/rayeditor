#include "rayeditor.hpp"

using namespace RayEditor::Docks;

/// <summary>
/// Draws and handles docks/menus UI.
/// </summary>
void DockManager::UpdateDocks() {
    for (size_t i = 0; i < activeDocks.size(); i++)
    {
        if (!activeDocks[i].operator Dock &().isInitialized)
        {
            activeDocks[i].operator Dock &().StartWindow();
            activeDocks[i].operator Dock &().isInitialized = true;
        }

        activeDocks[i].operator Dock &().DrawWindow();
    }
}

// <summary>
// Unitialize all docks and close them.
// </summary>
void DockManager::CloseDocks() {
    for (size_t i = 0; i < activeDocks.size(); i++)
    {
        activeDocks[i].operator Dock &().CloseWindow();
    }
}