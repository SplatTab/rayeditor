#include "rayeditor.hpp"
#include <rlImGui.h>
#include <filesystem>

using namespace RayEditor;
using namespace Docks;
using namespace Utility;
using namespace RLCommonUtils;
using namespace std::filesystem;

std::string currentProjectDirectory = Project::GetProjectDirectory();
std::string activeRelativeLocation;

// Global Icons
Texture2D folder;
Texture2D defaultFile;

void AssetDock::StartWindow() {
    // Load icons
    folder = LoadTexture("data\\icons\\folder.png");
    folder.width = 38;
    folder.height = 48;
    defaultFile = LoadTexture("data\\icons\\defaultfile.png");
    defaultFile.width = 36;
    defaultFile.height = 48;
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
        activeRelativeLocation = "";
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
    ImGui::NewLine();

    std::string copyBuffer;

    for (auto& file : files)
    {
        if (filterText[0] != '\0')
        {
            if (StringUtils::stristr(file.fileName.c_str(), filterText) == nullptr)continue;
        }

        ImGui::SameLine();
        if (rlImGuiImageButton(&file.icon))
        {
            if (file.isDirectory && file.isSelected)
            {
                if (file.fileName == "/..")
                {
                    activeRelativeLocation = activeRelativeLocation.substr(0, activeRelativeLocation.find_last_of('\\'));
                    RefreshFiles();
                }
                else
                {
                    activeRelativeLocation += "\\" + file.fileName;
                }
            }
            else
            {
                RefreshFiles();
                file.isSelected = true;
            }
        }

        if (copy) copyBuffer += file.fileName + "\r\n";
    }

    for (auto& file : files)
    {
        if (filterText[0] != '\0')
        {
            if (StringUtils::stristr(file.fileName.c_str(), filterText) == nullptr)continue;
        }

        ImGui::SameLine();

        if (file.isSelected)
        {
            ImGui::TextColored(Conversion::RayColorToImguiColor(BLUE), "%s", file.fileName.c_str());
        }
        else
        {
            ImGui::TextColored(Conversion::RayColorToImguiColor(RAYWHITE), "%s", file.fileName.c_str());
        }
    }

    if (copy) SetClipboardText(copyBuffer.c_str());
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

    // Up one folder file.
    FileInfo fileInfo;
    fileInfo.icon = folder;
    fileInfo.fileName = "/..";
    fileInfo.isDirectory = true;
    files.push_back(fileInfo);

    for (const auto & p : directory_iterator(Project::GetProjectDirectory() + activeRelativeLocation))
    {
        FileInfo fileInfo;
        if (p.is_directory())
        {
            fileInfo.icon = folder;
            fileInfo.isDirectory = true;
        }
        else
        {
            fileInfo.icon = defaultFile;
        }
        fileInfo.fileName = p.path().filename().string();

        files.push_back(fileInfo);
    }
}