#include "rayeditor.hpp"
#include <algorithm>

using namespace RayEditor;
using namespace Editor;

/// <summary>
/// Checks if a project is loaded.
/// </summary>
/// <returns>If a valid project directory is loaded</returns>
bool Project::IsProjectLoaded() {
    if (SetProjectDirectory(projectDir)) {
        return true;
    }

    return false;
}

/// <summary>
/// Gets the projects directory be sure to check if the project is loaded first.
/// </summary>
/// <returns>The active projects directory.</returns>
const char *Project::GetProjectDirectory() {
    return projectDir;
}

/// <summary>
/// Sets the project directory.
/// </summary>
/// <param name="projectPath">The directory.</param>
/// <returns>If the action was successful</returns>
bool Project::SetProjectDirectory(const char *projectPath) {

    if (projectPath == NULL) {
        return false;
    }

    std::string projectPathStr(projectPath);
    std::replace(projectPathStr.begin(), projectPathStr.end(), '/', '\\');

    if (projectPathStr.substr(projectPathStr.length() - 1) != "\\") projectPathStr += "\\";

    if (DirectoryExists(projectPath)) {
        if (FileExists((projectPathStr + "project.ray").c_str())) {
            static char projectPathText[2048] = { 0 };
            sprintf(projectPathText, "%s", projectPathStr.c_str());
            projectDir = projectPathText;
            return true;
        }
    }

    return false;
}