#pragma once
#include <raylib.h>
#include <imgui.h>
#include <string>
#include <vector>
#include <deque>
#include <functional>
#include <memory>

namespace RayEditor {

    #define EDITOR_VERSION "0.7.0" // The current editor version.

    struct LogItem {
        std::string prefix;
        std::string logText;
        Color logColor;
        int logType;
    }; // A log item used to store log messages.

    class Utility {
        public:

            static Vector2 RayVec2Add(Vector2 a, Vector2 b); // Add two vectors values.
            static Vector2 RayVec2Subtract(Vector2 a, Vector2 b); // Subtracts two vectors values.
            static Vector2 RayVec2Divide(Vector2 a, Vector2 b); // Divides two vectors values.
            static Vector2 RayVec2Multiply(Vector2 a, Vector2 b); // Multiplies two vectors values.
            static ImVec4 RayColorToImguiColor(Color color); // Converts a raylib color to an ImGui color.
            static std::string PatchErrorToString(int error); // Converts a patch error to a string.
            static char *stristr(const char *str1, const char * str2); // Checks if a string contains another string.
    }; // Basic Utilities such as conversion comparision and operators for editor tools.

    class Project {
        public:

            static std::string GetProjectDirectory(); // Gets the active project directory.
            static bool SetProjectDirectory(const char *projectPath); // Sets the active project directory.
            inline static bool IsProjectLoaded; // Is a project loaded?

        private:

            inline static std::string projectDir; // The modifiable active project directory this should not be manually set.
    }; // A class for managing the current project and it's directories.

    class Log {
        public:

            static void Info(std::string logText); // Logs a info message to the console dock.
            static void Debug(std::string logText); // Logs a debug message to the console dock.
            static void Warning(std::string logText); // Logs a warning message to the console dock.
            static void Error(std::string logText); // Logs a error message to the console dock.
            static void TraceLog(int logType, const char *text, va_list args); // Logs a message to the console dock.
    }; // A class for logging messages to the console dock for debugging purposes.

    class CachedIcons {
        public:

            static void LoadIcons(); // Loads default editor icons.
            static void UnloadIcons(); // Unloads default editor icons.

            inline static Texture2D folder; // The folder icon.
            inline static Texture2D defaultFile; // The default file icon.
            inline static Texture2D cameracenter; // The camera + marker icon.
    }; // A class for managing and getting cached editor icons.

        class Application {
            public:

                inline static bool recompiling; // Is the application recompiling a source file?
                inline static bool quit; // Is the editor quitting?

    }; // A class for managing the editor application.

    namespace Docks {

        class Console {
            public:

                static void DrawWindow(); // Draws the console dock.
                static void AddLog(LogItem logItem); // Adds a log item to the console dock.

            private:

                inline static std::vector<LogItem> logItems; // A list of log items should not be modified manually.
                inline static char filterText[512] = { 0 }; // The text in the search bar to filter the log items with stristr.
        }; // The console dock display debugging information and logs (static).

        class Dock {
            public:

                virtual ~Dock() = default; // Destructor.

                virtual void StartWindow() {}; // Initialize you're dock window.
                virtual void DrawWindow(int dockID) {}; // Draw you're dock window.
                virtual void CloseWindow() {}; // Unitialize you're dock window.
                bool isInitialized = false; // Is the dock initialized?
                bool open = true; // Is the dock open?
        }; // A base class for all docks.

        class AssetManager : public Dock {
            struct FileInfo {
                std::string fileName;
                std::string fileExtension;
                Texture2D icon;
                bool isSelected = false;
                bool isDirectory = false;
            }; // A file info struct used to store file information.

            public:

                void DrawWindow(int dockID) override; // Draws the asset dock.
                void RefreshFiles(); // Refreshes the files in the asset dock.

            private:

                std::vector<FileInfo> files; // A list of files in the asset dock.
                char filterText[512] = { 0 }; // The text in the search bar to filter the files with stristr.
                std::string currentProjectDirectory; // The current project directory.
                std::string prevRelativeLocation; // The last unupdated relative location of the asset dock.
                std::string activeRelativeLocation; // The active relative location of the asset dock.
        }; // A dock for navigating project files.

        class SceneView : public Dock {
            public:

                void StartWindow() override; // Setups the scene view dock.
                void DrawWindow(int dockID) override; // Draws the scene view dock.
                void ReloadRenderTexture(); // Reloads the render texture.
                void UpdateSceneView(); // Updates the scene rendered in the scene view dock.

            private:

                RenderTexture ViewTexture; // The render texture used to render the raylib view.
                Rectangle viewRect; // The source rectangle used to position the scene view.
                Camera2D camera; // The scene view camera
                Vector2 lastMousePos; // The last mouse position.
                Vector2 lastCamTarget; // The last camera target.
                ImVec2 size; // The size of the window.
                ImVec2 virtualRes; // The virtual resolution used to display the window.
                bool interactive; // Is the window focused and docked?
                bool dragging; // Is the camera being dragged?
        }; // A dock for viewing the current active scene.

        class DockManager {
            public:

                inline static int windowsOpen; // The number of open docks.
                static void UpdateDocks(); // Draw all open docks.
                static void CloseDocks(); // Unitialize all open docks.
                inline static std::deque<std::unique_ptr<Dock>> activeDocks; // A list of active docks.
        }; // The dock manager handles all docks.

        class ToolbarMenu {
            public:

                static void DrawWindow(); // Draws the toolbar dock.
        }; // The top bar of the editor (static).
    }
}