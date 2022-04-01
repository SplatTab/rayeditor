#include "rayeditor.hpp"
#include <filesystem>
#include <algorithm>

using namespace RayEditor;
using namespace std::filesystem;

/// <summary>
/// Gets the projects directory be sure to check if the project is loaded first.
/// </summary>
/// <returns>The active projects directory.</returns>
std::string Project::GetProjectDirectory() {
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

    path relativePath(projectPathStr);
    relativePath.remove_filename();

    if (DirectoryExists(relativePath.string().c_str())) {
        if (FileExists((relativePath.string() + "\\project.ray").c_str())) {
            path absolutePath = canonical(relativePath);

            IsProjectLoaded = true;
            projectDir = absolutePath.string();
            return true;
        }
    }

    return false;
}