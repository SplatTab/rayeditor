#include "rayeditor.hpp"
#include <rlImGui.h>
#include <filesystem>

using namespace RayEditor;
using namespace Docks;
using namespace Utility;
using namespace RLCommonUtils;
using namespace std::filesystem;

std::string currentProjectDirectory = Project::GetProjectDirectory();
std::string activeRelativeLocation = "\\";

// Global Icons
Texture2D folder;
Texture2D defaultFile;

void AssetDock::StartWindow() {
    // Load icons
    folder = LoadTexture("data\\icons\\folder.png");
    defaultFile = LoadTexture("data\\icons\\defaultfile.png");
}

void AssetDock::DrawWindow() {
    if (!Project::IsProjectLoaded) return;

    ImGui::Begin("Asset Manager");

    ImGui::SameLine();
    ImGui::SetNextItemWidth(200);
    ImGui::InputTextWithHint("###filterText", "Filter", filterText, 512);

    ImGui::SameLine();
    bool copy = false;

    if (Project::GetProjectDirectory() != currentProjectDirectory) {
        currentProjectDirectory = Project::GetProjectDirectory();
        activeRelativeLocation = "\\";
        RefreshFiles();
    }

    if(ImGui::Button("Copy"))
    {
        copy = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Refresh"))
    {
        RefreshFiles();
    }

    std::string copyBuffer;

    for (auto& file : files)
    {
        if (filterText[0] != '\0')
        {
            if (StringUtils::stristr(file.fileName.c_str(), filterText) == nullptr)continue;
        }

        if (rlImGuiImageButton(&file.icon))
        {
            Log::Debug("File clicked");
            file.isSelected = true;
        }
        ImGui::TextColored(Conversion::RayColorToImguiColor(RAYWHITE), "%s", file.fileName.c_str());
        if (copy)
            copyBuffer += file.fileName + "\r\n";
    }

    if (copy)
    {
        SetClipboardText(copyBuffer.c_str());
    }
    ImGui::End();
}

void AssetDock::CloseWindow() {
    UnloadTexture(folder);
    UnloadTexture(defaultFile);
    for (size_t i = 0; i < files.size(); i++)
    {
        UnloadTexture(files[i].icon);
    }
}

void AssetDock::RefreshFiles() {
    files.clear();

    for (const auto & p : directory_iterator(Project::GetProjectDirectory()))
    {
        FileInfo fileInfo;
        if (p.is_directory())
        {
            fileInfo.icon = folder;
            fileInfo.icon.width = 38;
            fileInfo.icon.height = 32;
            fileInfo.isDirectory = true;
        }
        else
        {
            fileInfo.icon = defaultFile;
            fileInfo.icon.width = 32;
            fileInfo.icon.height = 48;
        }
        fileInfo.fileName = p.path().filename().string();

        files.push_back(fileInfo);
    }
}