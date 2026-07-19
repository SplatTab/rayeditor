#include "rayeditor.hpp"
#include <repatcher.h>
#include <filesystem>
#include <algorithm>

using namespace RayEditor;
namespace fs = std::filesystem;

/// <summary>
/// Gets the projects directory be sure to check if the project is loaded first.
/// </summary>
/// <returns>The active projects directory.</returns>
std::string Project::GetProjectDirectory()
{
    return projectDir;
}

/// <summary>
/// Sets the project directory.
/// </summary>
/// <param name="projectPath">The directory.</param>
/// <returns>If the action was successful</returns>
bool Project::SetProjectDirectory(const char *projectPath)
{
    if (projectPath == NULL) return false;

    std::string projectPathStr(projectPath);

    fs::path relativePath(projectPathStr);
    relativePath.remove_filename();

    Log::Debug("Attempting to load project at: " + relativePath.string());
    if (fs::is_directory(relativePath)) {
        Log::Debug("Directory exists at: " + relativePath.string());
        fs::path projectFilePath = relativePath / "project.ray";
        printf("Checking for project.ray file at: %s\n", projectFilePath.string().c_str());
        if (fs::exists(projectFilePath)) {
            Log::Debug("Found project.ray file at: " + projectFilePath.string());
            fs::path absolutePath = canonical(relativePath);

            IsProjectLoaded = true;
            projectDir = absolutePath.string();
            printf("Project loaded at: %s\n", projectDir.c_str());
            REPatcher::SetTempLibaryPath((projectDir + "/temp/libs").c_str());

            return true;
        }
    }
    return false;
}