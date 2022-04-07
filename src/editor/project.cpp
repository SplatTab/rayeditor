#include "rayeditor.hpp"
#include <filesystem>
#include <algorithm>

using namespace RayEditor;
namespace fs = std::filesystem;

RPatcher_Context patcher;

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
            PatchError response = patcher.SetTempLibaryPath((projectDir + "\\temp\\libs").c_str());

            if (response == PATCH_ERROR_INVALID_PATH || response == PATCH_ERROR_NOT_DIRECTORY)
            {
                if (!fs::create_directories(projectDir + "\\temp\\libs")) return false;
            }

            for (const auto& p : fs::recursive_directory_iterator(projectDir))
            {
                if (p.is_directory()) {
                    for (const auto& subp : fs::directory_iterator(p))
                    {
                        if (subp.path().extension().string() == ".cpp")
                        {
                            patcher.AddSourceFile(subp.path().string().c_str(), "-Idata\\include", "-Ldata\\libs -lraylib");
                            Log::Debug("Added file: " + fs::absolute(subp).string());
                        }
                    }
                }
            }

            return true;
        }
    }

    return false;
}