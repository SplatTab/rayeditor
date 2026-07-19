/**********************************************************************************************
 * REPatcher is a library that allows you to load compile and execute libary's dynamically at runtime similar to unity behaviours.
 * LICENSE: GPL v3
 * Copyright (c) 2022 (SplatTab)
**********************************************************************************************/

#include "repatcher.h"
#include <filesystem>
#include <fstream>

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
std::vector<HMODULE> m_loadedLibs;
std::string dynamicFileType = ".dll";
#else
#include <sys/stat.h>
#include <dlfcn.h>
std::string dynamicFileType = ".so";
std::vector<void*> m_loadedLibs;
#endif

namespace fs = std::filesystem;

///<summary>
/// A temporary path to store the compiled libary and delete them.
///</summary>
PatchError REPatcher::SetTempLibaryPath(const char *path)
{
    fs::path filePath(path);

    if (!fs::exists(filePath))
    {
        if (!fs::create_directories(filePath)) return PATCH_ERROR_INVALID_PATH;
    }
    if (!fs::is_directory(filePath)) return PATCH_ERROR_NOT_DIRECTORY;

    m_tempLibaryPath = fs::absolute(filePath).string();

    return PATCH_ERROR_NO_ERROR;
}

///<summary>
/// A source file that will be compiled and loaded at runtime.
///</summary>
PatchError REPatcher::AddSourceFile(std::string path, std::string includePath, std::string libsPaths)
{
    fs::path filePath(path);
    std::string fileExtension = filePath.extension().string();
    fs::path absolutePath = fs::absolute(filePath);

    if (!fs::exists(filePath)) return PATCH_ERROR_INVALID_PATH;
    if (fs::is_directory(filePath)) return PATCH_ERROR_NOT_FILE;
    if (fileExtension != ".cpp" && fileExtension != ".c") return PATCH_ERROR_NOT_SOURCE_FILE;


    SourceFile sourceFile;
    sourceFile.absolutePath = absolutePath;
    sourceFile.includePaths = std::string(includePath);
    sourceFile.libPaths = std::string(libsPaths);
    sourceFile.lastTimeWritten = GetLastTimeWritten(absolutePath.string().c_str());
    Compile(sourceFile);

    m_sourceFiles.push_back(sourceFile);
    return AddLibary(sourceFile.dynamicLibaryPath.string().c_str());
}

///<summary>
/// Checks if libaries are modified and recompile and update them if they are
///</summary>
UpdateResult REPatcher::Update()
{
    UpdateResult result;
    result.wasRecompiled = false;
    result.compileErrors = false;
    result.recompiledFiles.clear();

    for (auto &sourceFile : m_sourceFiles) {
        int64_t currentLastWriteTime = GetLastTimeWritten(sourceFile.absolutePath.string().c_str());

        if (sourceFile.lastTimeWritten != currentLastWriteTime)
        {
            sourceFile.lastTimeWritten = currentLastWriteTime;
            if (!Compile(sourceFile))
            {
                result.compileErrors = true;
                result.failedFiles.push_back(sourceFile);
            } else {
                result.recompiledFiles.push_back(sourceFile);
            }
            UnloadAll();
            m_rayBehaviours.clear();
            for (auto &reloadSource : m_sourceFiles) AddLibary(reloadSource.dynamicLibaryPath.string().c_str());
            AddLibary(sourceFile.dynamicLibaryPath.string().c_str());
            result.wasRecompiled = true;
        }
    }

    return result;
}

//<summary>
// Gets a files last time of modification
//</summary>
int64_t REPatcher::GetLastTimeWritten(const char *path)
{
    #if defined(_WIN32) || defined(_WIN64)
    // Get the last time a file was modified realtime for windows
    HANDLE hFile = CreateFileA(LPCSTR(path), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return 0;
    FILETIME ftWrite;
    if (!GetFileTime(hFile, NULL, NULL, &ftWrite)) return 0;
    CloseHandle(hFile);
    return (int64_t)ftWrite.dwLowDateTime;
    #else
    struct stat fileStat;
    if (stat(path, &fileStat) == 0) return -1;
    return (int64_t)fileStat.st_mtime;
    #endif
}

///<summary>
/// Compiles a source file into a dynamic libary.
///</summary>
/// <returns>Returns true if the compilation was successful, false otherwise.</returns>
bool REPatcher::Compile(SourceFile &sourceFile)
{
    std::string outputFile = m_tempLibaryPath + "/" + sourceFile.absolutePath.stem().filename().replace_extension(".o").string(); // The compiled source file output path.
    fs::path outputDynamicFile = sourceFile.absolutePath.filename().replace_extension(dynamicFileType); // The compiled dynamic libary output path.
    std::string oldDynamicFile = m_tempLibaryPath + "/" + sourceFile.dynamicLibaryPath.filename().replace_extension(dynamicFileType + ".old").string(); // The renamed old dynamic libary path.
    std::string outputDynamicFilePath = m_tempLibaryPath + "/" + outputDynamicFile.filename().string(); // The compiled dynamic libary output path in temp libs folder.

    std::remove("compile_errors.txt"); // Remove the compile errors file if it exists.
    std::string compileCommand =
    "g++ -c " + sourceFile.absolutePath.string() +
    " -o " + outputFile +
    " " + sourceFile.includePaths +
    " " + sourceFile.libPaths +
    " 2> compile_errors.txt";

    int result = system(compileCommand.c_str());

    if (result != 0)
    {
        std::ifstream errorFile("compile_errors.txt");
        std::string errors((std::istreambuf_iterator<char>(errorFile)), std::istreambuf_iterator<char>());

        sourceFile.lastCompileError = errors;
        return false;
    }

    std::remove("compile_errors.txt"); // Remove the compile errors file if it exists.
    std::string linkCommand = "g++ -shared -o " + outputDynamicFile.filename().string()
    + " " + outputFile + " " + sourceFile.libPaths + " 2> compile_errors.txt";
    int linkResult = system(linkCommand.c_str());
    if (linkResult != 0)
    {
        std::ifstream errorFile("compile_errors.txt");
        std::string errors((std::istreambuf_iterator<char>(errorFile)), std::istreambuf_iterator<char>());

        sourceFile.lastCompileError = errors;
        return false;
    }

    if (fs::exists(sourceFile.dynamicLibaryPath))
    {
        fs::rename(sourceFile.dynamicLibaryPath.string().c_str(), oldDynamicFile.c_str()); // Rename the old dynamic libary.
        if (fs::exists(oldDynamicFile)) std::remove(oldDynamicFile.c_str()); // Remove the old dynamic libary.
    }

    if (fs::exists(outputFile)) std::remove(outputFile.c_str());

    if (fs::exists(outputDynamicFile)) fs::rename(outputDynamicFile, outputDynamicFilePath);

    sourceFile.dynamicLibaryPath = fs::path(outputDynamicFilePath);
    return true;
}

///<summary>
/// Lodas a specific libary and extracts the raybehaviour from it.
///</summary>
PatchError REPatcher::AddLibary(const char* path) {
    if (!fs::exists(path)) return PATCH_ERROR_INVALID_PATH;

    #if defined(_WIN32) || defined(_WIN64)
    HMODULE lib = LoadLibraryA(LPCSTR(path));
    if (lib == NULL)
    {
        FreeLibrary(lib);
        return PATCH_ERROR_DYNAMIC_LIB_NOT_LOADED;
    }

    RObjCreator CreateRayObj = (RObjCreator)(GetProcAddress(lib, "GetBehaviour"));
    RObjDeletor DeleteRayObj = (RObjDeletor)(GetProcAddress(lib, "KillBehaviour"));
    IRayBehaviour* RayObj = CreateRayObj();

    if (CreateRayObj == NULL || DeleteRayObj == NULL || RayObj == NULL)
    {
        DeleteRayObj(RayObj);
        FreeLibrary(lib);
        return PATCH_ERROR_FAILED_EXTRACTION;
    }
    #else
    void* lib = dlopen(path, RTLD_LAZY);
    if (lib == NULL)
    {
        dlclose(lib);
        return PATCH_ERROR_DYNAMIC_LIB_NOT_LOADED;
    }

    RObjCreator CreateRayObj = (RObjCreator)(dlsym(lib, "GetBehaviour"));
    RObjDeletor DeleteRayObj = (RObjDeletor)(dlsym(lib, "KillBehaviour"));
    IRayBehaviour* RayObj = CreateRayObj();

    if (RayObj == NULL)
    {
        DeleteRayObj(RayObj);
        dlclose(lib);
        return PATCH_ERROR_FAILED_EXTRACTION;
    }
    #endif

    m_loadedLibs.push_back(lib);
    m_rayBehaviours.push_back(RayObject{ CreateRayObj, DeleteRayObj, RayObj });

    return PATCH_ERROR_NO_ERROR;
}

// Frees all ray behaviours and libaries.
void REPatcher::UnloadAll()
{
    for (auto& obj : m_rayBehaviours) obj.DeleteRayObj(obj.RayObj);

    #if defined(_WIN32) || defined(_WIN64)
    for (auto& lib : m_loadedLibs) FreeLibrary(lib);
    #else
    for (auto& lib : m_loadedLibs) dlclose(lib);
    #endif
}