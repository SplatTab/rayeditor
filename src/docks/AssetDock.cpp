#include "rayeditor.hpp"
#include <filesystem>

using namespace RayEditor;
using namespace Docks;
using namespace Editor;
using namespace Utility;
using namespace RLCommonUtils;
using namespace std::filesystem;

void AssetDock::DrawWindow() {
    ImGui::Begin("Asset Manager");

    ImGui::SameLine();
    ImGui::SetNextItemWidth(200);
    ImGui::InputTextWithHint("###filterText", "Filter", filterText, 512);

    ImGui::SameLine();
    bool copy = false;
    if(ImGui::Button("Copy"))
    {
        copy = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Refresh"))
    {
        // Get every file in the project directory
        files.clear();
        for (const auto & p : directory_iterator(Project::GetProjectDirectory()))
        {
            files.push_back(p.path().string());
        }
    }

    std::string copyBuffer;

    for (auto& line : files)
    {
        if (filterText[0] != '\0')
        {
            if (StringUtils::stristr(line.c_str(), filterText) == nullptr)continue;
        }
        ImGui::TextColored(Conversion::RayColorToImguiColor(RAYWHITE), "%s", line.c_str());
        if (copy)
            copyBuffer += line + "\r\n";
    }

    if (copy)
    {
        SetClipboardText(copyBuffer.c_str());
    }
    ImGui::End();
}