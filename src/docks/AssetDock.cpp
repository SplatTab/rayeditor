#include "rayeditor.hpp"

using namespace RayEditor;
using namespace Docks;
using namespace Utility;
using namespace RLCommonUtils;

void AssetDock::DrawWindow() {
    if (!ImGui::Begin("Asset Manager"))
    {
        ImGui::End();
    }

    ImGui::SameLine();
    ImGui::SetNextItemWidth(200);
    ImGui::InputTextWithHint("###filterText", "Filter", FilterText, 512);

    ImGui::SameLine();
    bool copy = false;
    if(ImGui::Button("Copy"))
    {
        copy = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Refresh"))
    {
        files.clear();
        int count = 0;
        char** dirfiles = GetDirectoryFiles(GetApplicationDirectory(), &count);
        std::string filesstr = std::string((char*)dirfiles);
        files.push_back(filesstr);
        free(dirfiles);
    }

    std::string copyBuffer;

    for (auto& line : files)
    {
        if (FilterText[0] != '\0')
        {
            if (StringUtils::stristr(line.c_str(), FilterText) == nullptr)
                continue;
        }
        ImGui::TextColored(Conversion::RayColorToImguiColor(RAYWHITE), "%s", line.c_str());
        ImGui::SameLine();
        if (copy)
            copyBuffer += line + "\r\n";
    }

    if (copy)
    {
        SetClipboardText(copyBuffer.c_str());
    }
    ImGui::End();
}