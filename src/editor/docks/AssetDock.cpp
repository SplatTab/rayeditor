#include "rayeditor.hpp"
#include "raystyles.hpp"
#include <rlImGui.h>
#include <filesystem>

using namespace RayEditor;
using namespace Docks;
using namespace Utility;
using namespace RLCommonUtils;
using namespace std::filesystem;

std::string currentProjectDirectory = Project::GetProjectDirectory();
std::string prevRelativeLocation;
std::string activeRelativeLocation;

Texture2D folder;
Texture2D defaultFile;

void AssetDock::StartWindow() {
    folder = LoadTexture("data\\icons\\folder.png");
    folder.width = 74;
    folder.height = 84;

    defaultFile = LoadTexture("data\\icons\\defaultfile.png");
    defaultFile.width = 72;
    defaultFile.height = 84;
}

void AssetDock::DrawWindow() {
    if (!Project::IsProjectLoaded) return;

    if (Project::GetProjectDirectory() != currentProjectDirectory) {
        currentProjectDirectory = Project::GetProjectDirectory();
        prevRelativeLocation = "";
        activeRelativeLocation = "";
        RefreshFiles();
    }

    if (prevRelativeLocation != activeRelativeLocation) {
        prevRelativeLocation = activeRelativeLocation;
        RefreshFiles();
    }

    ImGui::Begin("Asset Manager");

    ImGui::SameLine();
    ImGui::SetNextItemWidth(200);
    ImGui::InputTextWithHint("###filterText", "Filter", filterText, 512);
    ImGui::SameLine();

    bool copy = false;

    if(ImGui::Button("Copy"))
        copy = true;

    ImGui::SameLine();

    if (ImGui::Button("Refresh"))
        RefreshFiles();

    ImGui::Text(("Path: " + currentProjectDirectory + activeRelativeLocation).c_str());

    std::string copyBuffer;

    if (!ImGui::BeginTable("###assetsTable", 64, ImGuiTableFlags_SizingFixedSame) || files.size() >= 64) {
        ImGui::End();
        return;
    }

    PushStyle::TransparentTable();
    ImGui::TableHeadersRow();

    for (auto& file : files)
    {
        if (filterText[0] != '\0')
            if (StringUtils::stristr(file.fileName.c_str(), filterText) == nullptr)continue;

        ImGui::TableNextColumn();

        if (ImGui::CalcTextSize(file.fileName.c_str()).x > file.icon.width) ImGui::TableHeader((file.fileName.substr(0, 7) + "..").c_str());
        else ImGui::TableHeader(file.fileName.substr(0, 7).c_str());

        if (rlImGuiImageButton(&file.icon))
        {
            if (file.isDirectory && file.isSelected)
            {
                file.isSelected = false;
                if (file.fileExtension == "UpOneFolder\\//") activeRelativeLocation = activeRelativeLocation.substr(0, activeRelativeLocation.find_last_of('\\'));
                else activeRelativeLocation += "\\" + file.fileName;
            }
            else
            {
                file.isSelected = true;
            }
        }

        if (copy) copyBuffer += file.fileName + file.fileExtension + "\r\n";
    }

    if (copy) SetClipboardText(copyBuffer.c_str());

    PopStyle::TransparentTable();
    ImGui::EndTable();
    ImGui::End();
}

void AssetDock::CloseWindow() {
    UnloadTexture(folder);
    UnloadTexture(defaultFile);
    for (size_t i = 0; i < files.size(); i++) UnloadTexture(files[i].icon);
}

void AssetDock::RefreshFiles() {
    files.clear();

    FileInfo fileInfo;
    fileInfo.icon = folder;
    fileInfo.fileName = "..";
    fileInfo.fileExtension = "UpOneFolder\\//";
    fileInfo.isDirectory = true;
    files.push_back(fileInfo);

    if (!std::filesystem::exists(currentProjectDirectory + activeRelativeLocation))
    {
        currentProjectDirectory = Project::GetProjectDirectory();
        prevRelativeLocation = "";
        activeRelativeLocation = "";
    }

    for (const auto & p : directory_iterator(currentProjectDirectory + activeRelativeLocation))
    {
        if (p.is_directory())
        {
            fileInfo.icon = folder;
            fileInfo.isDirectory = true;
        }
        else
        {
            fileInfo.icon = defaultFile;
        }

        std::string fileExtension = p.path().filename().extension().string();
        std::string fileName = p.path().filename().string();
        fileInfo.fileName = fileName.substr(0, fileName.length() - fileExtension.length());
        fileInfo.fileExtension = fileExtension;

        files.push_back(fileInfo);
    }
}