#include "rayeditor.hpp"

using namespace RayEditor::Utility;

ImVec4 Conversion::RayColorToImguiColor(Color color) {
    return ImVec4(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
}