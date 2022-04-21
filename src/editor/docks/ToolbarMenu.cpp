#include "rayeditor.hpp"
#include <imgui_filedialog.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

using namespace RayEditor;
using namespace Docks;
namespace json = rapidjson;

bool dialogEditorSettingsOpen;
bool dialogOpenProjectOpen;
ImFileDialogInfo dialogOpenProjectInfo;

void SelectProjectDialog();
void EditorSettingsDialog(bool &p_open);

void ToolbarMenu::DrawWindow()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if ((ImGui::MenuItem("Open Project", "CTRL+SHIFT+O") || (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_O))) && !dialogOpenProjectOpen) SelectProjectDialog();
            if (ImGui::MenuItem("Settings", "F7") || IsKeyPressed(KEY_F7)) std::exchange(dialogEditorSettingsOpen, !dialogEditorSettingsOpen);

            if (ImGui::MenuItem("Exit", "Alt+F4")) Application::quit = true;
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Asset Manager") && Project::IsProjectLoaded) DockManager::activeDocks.push_back(std::make_unique<AssetManager>());
            if (ImGui::MenuItem("Scene View") && Project::IsProjectLoaded) DockManager::activeDocks.push_back(std::make_unique<SceneView>());
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    if (ImGui::FileDialog(&dialogOpenProjectOpen, &dialogOpenProjectInfo))
    {
        if (Project::SetProjectDirectory(dialogOpenProjectInfo.resultPath.string().c_str())) Log::Info("Project loaded: " + std::string(Project::GetProjectDirectory()));
        else Log::Warning("Project could not be loaded check that this is a valid project directory with a project.ray file.");
    }

    if(dialogEditorSettingsOpen) EditorSettingsDialog(dialogEditorSettingsOpen);
}

///<summary>
/// Opens a file dialog to select a project file.
///</summary>
void SelectProjectDialog()
{
    dialogOpenProjectOpen = true;
    dialogOpenProjectInfo.type = ImGuiFileDialogType_OpenFile;
    dialogOpenProjectInfo.title = "Select Project File";
    dialogOpenProjectInfo.directoryPath = std::filesystem::current_path();
}

void EditorSettingsDialog()
{
    if (ImGui::Begin("Editor Settings"), dialogEditorSettingsOpen)
    {
        json::StringBuffer s;
        json::Writer<json::StringBuffer> writer(s);

        writer.StartObject();
        writer.Key("TraceLogCallback");
        writer.Bool(true);
        writer.EndObject();
        ImGui::Text(s.GetString());
    }

    ImGui::End();
}