#include "rayeditor.hpp"
#include <raypatcher.h>
#include <filesystem>
#include <algorithm>

using namespace RayEditor;
namespace fs = std::filesystem;

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

    if (projectPath == NULL) return false;

    std::string projectPathStr(projectPath);
    std::replace(projectPathStr.begin(), projectPathStr.end(), '/', '\\');

    fs::path relativePath(projectPathStr);
    relativePath.remove_filename();

    if (DirectoryExists(relativePath.string().c_str())) {
        if (FileExists((relativePath.string() + "\\project.ray").c_str())) {
            fs::path absolutePath = canonical(relativePath);

            IsProjectLoaded = true;
            projectDir = absolutePath.string();
            RPatcher::SetTempLibaryPath((projectDir + "/temp/libs").c_str());

            return true;
        }
    }

    return false;
}