#include "rayeditor.hpp"

using namespace RayEditor;
using namespace Docks;

void Console::DrawWindow()
{
    if (ImGui::Begin("Console"))
    {
        ImGui::SameLine();
        ImGui::SetNextItemWidth(200);
        ImGui::InputTextWithHint("###filterText", "Filter", filterText, 512);
        ImGui::SameLine();

        bool copy = false;
        if(ImGui::Button("Copy")) copy = true;

        ImGui::SameLine();

        if (ImGui::Button("Clear")) logItems.clear();

        std::string copyBuffer;

        for (auto& line : logItems)
        {
            if (filterText[0] != '\0')
            {
                if (Utility::stristr(line.logText.c_str(), filterText) == nullptr) continue;
            }

            ImGui::TextColored(Utility::RayColorToImguiColor(line.logColor), "%s", line.prefix.c_str());
            ImGui::SameLine();
            ImGui::TextUnformatted(line.logText.c_str());

            if (copy) copyBuffer += line.prefix + line.logText + "\r\n";
        }

        if (copy) SetClipboardText(copyBuffer.c_str());
    }

    ImGui::End();
}

/// <summary>
/// Adds a log item to the console to be drawn.
/// </summary>
/// <param name="logItem">The LogItem to be added to the logs.</param>
void Console::AddLog(LogItem logItem)
{
    logItems.push_back(logItem);
}