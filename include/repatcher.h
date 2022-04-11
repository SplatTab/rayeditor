/**********************************************************************************************
 * REPatcher is a library that allows you to load compile and execute libary's dynamically at runtime similar to unity behaviours.
 * LICENSE: ZLIB
 * Copyright (c) 2022 (SplatTab)
**********************************************************************************************/
#pragma once
#include <vector>
#include <filesystem>
#include <string>

class IRayBehaviour {
    public:

        virtual ~IRayBehaviour() = default;

        virtual void Init() {};
        virtual void Update() {};
        virtual void Draw() {};
        virtual void Close() {};
}; // Ray Behavior is the only thing needed for patches and is the base class for all ray behaviours.

typedef IRayBehaviour*(*RObjCreator)(); // A function pointer that creates a ray behaviour.
typedef void(*RObjDeletor)(IRayBehaviour*); // A function pointer that deletes a ray behaviour.

typedef struct {
    RObjCreator CreateRayObj; // Object creator
    RObjDeletor DeleteRayObj; // Object deletor
    IRayBehaviour* RayObj; // The ray behaviour
} RayObject; // A ray object is a ray behaviour with a creator and a deleter.

typedef struct {
    std::filesystem::path absolutePath; // The absolute path to the source file.
    std::filesystem::path dynamicLibaryPath; // The absolute path to this source files current dynamic libary.
    std::string includePaths; // The include paths for the ray behaviour.
    std::string libPaths; // The lib paths for the ray behaviour.
    int64_t lastTimeWritten; // The last time the file was modified.
} SourceFile; // Info about a source file that will be compiled and loaded at runtime if modified.

enum PatchError {
    PATCH_ERROR_NO_ERROR, // No error operation was performed.
    PATCH_ERROR_INVALID_PATH, // The file does not exist or the path is invalid.
    PATCH_ERROR_NOT_FILE, // The path is a directory.
    PATCH_ERROR_NOT_DIRECTORY, // The path is a fail.
    PATCH_ERROR_NOT_SOURCE_FILE, // The file is not a C or C++ source file.
    PATCH_ERROR_FAILED_EXTRACTION, // Failed to extract the address of the ray behaviour.
    PATCH_ERROR_DYNAMIC_LIB_NOT_LOADED // The dynamic libary couldn't be loaded.
};

class REPatcher {
    public:

        // Regular libary functions
        static PatchError SetTempLibaryPath(const char *path); // Setup a temporary path to manage the compiled libaries.
        static PatchError AddSourceFile(const char *path, const char *includePath, const char *libsPaths); // Add a source file to the context to be updated.
        static bool Update(); // Update the context and do things like check if libaries need to be recompiled and recompile them.
        static void UnloadAll(); // Unloads all ray behaviours. Note: Should be called at the end of you're program or to wipe all ray behaviours and source files.
        inline static std::vector<RayObject> m_rayBehaviours; // A list of ray behaviours for you're program.

        // Advanced System stuff. Note: Should not be used manually but still available.
        static int64_t GetLastTimeWritten(const char *path); // Get the last time a file was modified.
        static std::string Compile(SourceFile sourceFile); // Compiles a source file and returns the path to the dynamic compiled libary.
        static PatchError AddLibary(const char *path); // Extracts a ray behaviour from a libary and adds it to ray behaviours.
        inline static std::vector<SourceFile> m_sourceFiles; // A list of source files.

    private:

        inline static std::string m_tempLibaryPath; // The current temp libary directory path.
}; // A ray patcher context is the main class where you specify source files and other info.