#include "raystyles.hpp"

///<summary>
/// Pushes a transparent table with no colors for headers, buttons, etc style onto the style stack.
///</summary>
void PushStyle::TransparentTable() {
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32_BLACK_TRANS);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32_BLACK_TRANS);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32_BLACK_TRANS);
    ImGui::PushStyleColor(ImGuiCol_TableHeaderBg, IM_COL32_BLACK_TRANS);
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, IM_COL32_BLACK_TRANS);
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, IM_COL32_BLACK_TRANS);
}

void PopStyle::TransparentTable() {
    ImGui::PopStyleColor(6);
}