#include "rayeditor.hpp"
#include "imgui_filedialog.h"

using namespace RayEditor;
using namespace Docks;
using namespace Utility;
using namespace Editor;

bool dialogOpenProjectOpen;
ImFileDialogInfo dialogOpenProjectInfo;

void SelectProjectDialog();

void ToolbarDock::DrawWindow() {
    if (ImGui::BeginMenuBar())
    {
        if ((IsKeyDown(KEY_LEFT_CONTROL) & IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_O)) && !dialogOpenProjectOpen)
        {
            SelectProjectDialog();
        }

        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open Project", "CTRL+SHIFT+O") && !dialogOpenProjectOpen)
            {
                SelectProjectDialog();
            }

            if (ImGui::MenuItem("Exit", "Alt+F4")) Editor::Application::quit = true;
            ImGui::EndMenu();
        }

        if (ImGui::FileDialog(&dialogOpenProjectOpen, &dialogOpenProjectInfo))
        {
            if (Project::SetProjectDirectory(dialogOpenProjectInfo.resultPath.string().c_str())) {
                Log::Info("Project loaded: " + std::string(Project::GetProjectDirectory()));
            }
            else
            {
                Log::Warning("Project could not be loaded check that this is a valid project directory with a project.ray file.");
            }
        }

        ImGui::EndMenuBar();
    }
}

void SelectProjectDialog() {
    dialogOpenProjectOpen = true;
    dialogOpenProjectInfo.type = ImGuiFileDialogType_OpenFile;
    dialogOpenProjectInfo.title = "Select Project File";
    dialogOpenProjectInfo.directoryPath = std::filesystem::current_path();
}