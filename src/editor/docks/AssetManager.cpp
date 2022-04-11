#include "rayeditor.hpp"
#include "raystyles.hpp"
#include <repatcher.h>
#include <rlImGui.h>
#include <filesystem>

using namespace RayEditor;
using namespace Docks;
namespace fs = std::filesystem;

void AssetManager::DrawWindow(int dockID)
{
    if (!open)
    {
        DockManager::activeDocks.erase(DockManager::activeDocks.begin() + (dockID));
        return;
    }

    if (!Project::IsProjectLoaded) return;

    if (Project::GetProjectDirectory() != currentProjectDirectory)
    {
        currentProjectDirectory = Project::GetProjectDirectory();
        activeRelativeLocation = "";
        prevRelativeLocation = "0";
    }

    if (prevRelativeLocation != activeRelativeLocation)
    {
        prevRelativeLocation = activeRelativeLocation;
        RefreshFiles();
    }

    if (ImGui::Begin(("Asset Manager##" + std::to_string(dockID)).c_str(), &open))
    {
        ImGui::SameLine();
        ImGui::SetNextItemWidth(200);
        ImGui::InputTextWithHint("###filterText", "Filter", filterText, 512);
        ImGui::SameLine();

        bool copy = false;
        if(ImGui::Button("Copy")) copy = true;

        ImGui::SameLine();

        if (ImGui::Button("Refresh")) RefreshFiles();

        ImGui::Text(("Path: " + currentProjectDirectory + activeRelativeLocation).c_str());

        std::string copyBuffer;

        if (!ImGui::BeginTable("###assetsTable", 8, ImGuiTableFlags_SizingFixedSame)) {
            ImGui::End();
            return;
        }

        PushStyle::TransparentTable();
        ImGui::TableHeadersRow();

        for (size_t i = 0; i < files.size(); i++)
        {
            if (filterText[0] != '\0')
            {
                if (Utility::stristr(files[i].fileName.c_str(), filterText) == nullptr) continue;
            }

            if (ImGui::GetColumnIndex() == 7) ImGui::TableNextRow();

            ImGui::TableNextColumn();

            if (ImGui::CalcTextSize(files[i].fileName.c_str()).x > files[i].icon.width) ImGui::TableHeader((files[i].fileName.substr(0, 7) + "..").c_str());
            else ImGui::TableHeader(files[i].fileName.substr(0, 8).c_str());

            if (rlImGuiImageButton(&files[i].icon))
            {
                if (files[i].isDirectory && files[i].isSelected)
                {
                    files[i].isSelected = false;
                    if (files[i].fileExtension == "UpOneFolder\\//") activeRelativeLocation = activeRelativeLocation.substr(0, activeRelativeLocation.find_last_of('\\'));
                    else activeRelativeLocation += "\\" + files[i].fileName;
                }
                else
                {
                    files[i].isSelected = true;
                }
            }

            if (copy) copyBuffer += files[i].fileName + files[i].fileExtension + "\r\n";
        }

        if (copy) SetClipboardText(copyBuffer.c_str());

        PopStyle::TransparentTable();
        ImGui::EndTable();
    }

    ImGui::End();
}

///<summary>
/// Refreshes the current files with the active directory's files.
///</summary>
void AssetManager::RefreshFiles()
{
    files.clear();

    FileInfo fileInfo;
    fileInfo.icon = CachedIcons::folder;
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

    for (const auto & p : fs::directory_iterator(currentProjectDirectory + activeRelativeLocation))
    {
        if (p.is_directory())
        {
            fileInfo.icon = CachedIcons::folder;
            fileInfo.isDirectory = true;
        }
        else
        {
            fileInfo.icon = CachedIcons::defaultFile;
        }

        std::string fileExtension = p.path().filename().extension().string();
        std::string fileName = p.path().filename().string();
        fileInfo.fileName = fileName.substr(0, fileName.length() - fileExtension.length());
        fileInfo.fileExtension = fileExtension;

        files.push_back(fileInfo);
    }

    for (const auto& p : fs::recursive_directory_iterator(Project::GetProjectDirectory()))
    {
        if (p.is_directory())
        {
            for (const auto& subp : fs::directory_iterator(p))
            {
                if (subp.path().extension().string() == ".cpp")
                {
                    bool available = true;
                    for (SourceFile file : REPatcher::m_sourceFiles)
                    {
                        if (file.absolutePath == subp.path().string()) available = false;
                    }

                    if (available)
                    {
                        #ifdef _WIN32
                        PatchError error = REPatcher::AddSourceFile(subp.path().string().c_str(), "-Idata\\include\\", "-L. -Ldata\\libs\\ -lraylib -lopengl32 -lgdi32 -lwinmm -lws2_32");
                        #elif __linux__
                        PatchError error = REPatcher::AddSourceFile(subp.path().string().c_str(), "-Idata\\include\\", "-L. -Ldata\\libs\\ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11");
                        #endif
                        if (error != PATCH_ERROR_NO_ERROR) Log::Error("Source file: " + subp.path().string() + " could not be loaded. Error: " + Utility::PatchErrorToString(error));
                    }
                }
            }
        }
    }
}