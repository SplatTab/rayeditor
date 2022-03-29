#include "rayeditor.hpp"

using namespace RayEditor;
using namespace Docks;

void DockManager::DrawDocks() {
    ConsoleDock::DrawWindow();
    AssetDock::DrawWindow();
}