#include "rayeditor.hpp"
#include "editorstyles.hpp"
#include <rlImGui.h>
#include <filesystem>

using namespace RayEditor;
using namespace Docks;
using namespace Utility;
using namespace RLCommonUtils;
using namespace std::filesystem;

std::string currentProjectDirectory = Project::GetProjectDirectory();
std::string activeRelativeLocation;

Texture2D folder;
Texture2D defaultFile;

void AssetDock::StartWindow() {
    folder = LoadTexture("data\\icons\\folder.png");
    folder.width = 54;
    folder.height = 64;

    defaultFile = LoadTexture("data\\icons\\defaultfile.png");
    defaultFile.width = 52;
    defaultFile.height = 64;
}

void AssetDock::DrawWindow() {
    if (!Project::IsProjectLoaded) return;

    ImGui::Begin("Asset Manager");

    ImGui::SameLine();
    ImGui::SetNextItemWidth(200);
    ImGui::InputTextWithHint("###filterText", "Filter", filterText, 512);
    ImGui::SameLine();

    if (Project::GetProjectDirectory() != currentProjectDirectory) {
        currentProjectDirectory = Project::GetProjectDirectory();
        activeRelativeLocation = "";
        RefreshFiles();
    }

    bool copy = false;

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

    if (!ImGui::BeginTable("###assetsTable", 64, ImGuiTableFlags_SizingFixedSame)) {
        ImGui::End();
        return;
    }

    ImGui::TableHeadersRow();
    PushStyle::TransparentTable();

    for (auto& file : files)
    {
        if (filterText[0] != '\0')
        {
            if (StringUtils::stristr(file.fileName.c_str(), filterText) == nullptr)continue;
        }

        ImGui::TableNextColumn();

        if (ImGui::CalcTextSize(file.fileName.c_str()).x > file.icon.width) ImGui::TableHeader((file.fileName.substr(0, 7) + "..").c_str());
        else ImGui::TableHeader(file.fileName.c_str());

        if (rlImGuiImageButton(&file.icon))
        {
            if (file.isDirectory && file.isSelected)
            {
                if (file.fileName == "/..") activeRelativeLocation = activeRelativeLocation.substr(0, activeRelativeLocation.find_last_of('\\'));
                else activeRelativeLocation += "\\" + file.fileName;
                RefreshFiles();
            }
            else
            {
                RefreshFiles();
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

    // Up one folder file.
    FileInfo fileInfo;
    fileInfo.icon = folder;
    fileInfo.fileName = "/..";
    fileInfo.isDirectory = true;
    files.push_back(fileInfo);

    if (!std::filesystem::exists(Project::GetProjectDirectory() + activeRelativeLocation)) activeRelativeLocation = "";

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

        std::string fileExtension = p.path().filename().extension().string();
        std::string fileName = p.path().filename().string();
        fileInfo.fileName = fileName.substr(0, fileName.length() - fileExtension.length());
        fileInfo.fileExtension = fileExtension;

        files.push_back(fileInfo);
    }
}