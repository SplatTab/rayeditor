#include "rayeditor.hpp"

using namespace RayEditor;
using namespace Docks;

void TopMenuDock::DrawWindow() {
    ImGui::MenuItem("File/Open Project", "Ctrl+Shift+O", &projectOpening);
    ImGui::MenuItem("File/New Project", "Ctrl+Shift+N", &creatingProject);
}