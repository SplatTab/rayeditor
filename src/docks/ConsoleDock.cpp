#include "rayeditor.hpp"

using namespace RayEditor;
using namespace Docks;
using namespace Utility;
using namespace RLCommonUtils;

void ConsoleDock::DrawWindow() {
    if (!ImGui::Begin("Console"))
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
    if (ImGui::Button("Clear"))
    {
        logItems.clear();
    }

    std::string copyBuffer;

    for (auto& line : logItems)
    {
        if (FilterText[0] != '\0')
        {
            if (StringUtils::stristr(line.logText.c_str(), FilterText) == nullptr)
                continue;
        }
        ImGui::TextColored(Conversion::RayColorToImguiColor(line.logColor), "%s", line.prefix.c_str());
        ImGui::SameLine();
        ImGui::TextUnformatted(line.logText.c_str());
        if (copy)
            copyBuffer += line.prefix + line.logText + "\r\n";
    }

    if (copy)
    {
        SetClipboardText(copyBuffer.c_str());
    }
    ImGui::End();
}

void ConsoleDock::AddLog(LogItem logItem) {
    ConsoleDock::logItems.push_back(logItem);
}