#pragma once
#include <raylib.h>
#include <imgui.h>
#include <string>
#include <vector>
#include <deque>
#include <functional>
#include <memory>

namespace RayEditor {

    #define EDITOR_VERSION "0.5.0" // The current editor version.

    struct LogItem {
        std::string prefix;
        std::string logText;
        Color logColor;
        int logType;
    }; // A log item used to store log messages.

    namespace Utility {
        class Conversion {
            public:

                static ImVec4 RayColorToImguiColor(Color color); // Converts a raylib color to an ImGui color. Note: Should only be used for editor tools.
        };

        namespace RLCommonUtils {

            class StringUtils {
                public:

                    static char *stristr(const char *str1, const char * str2); // Checks if a string contains another string. Note: Should only be used for editor tools.
            }; // A set of utilies for string manipulation.
        }
    } // The namespace utitlity contains a set of utilities to make you're life easier.

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
    }; // A class for managing and getting cached editor icons.

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
                void UpdateSceneView(); // Updates the scene rendered in the scene view dock.

            private:

                RenderTexture ViewTexture; // The render texture used to render the raylib view.
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

                struct MenuItem {
                    std::string container;
                    std::string name;
                    std::function<void()> onClick;
                }; // A menu item struct used to store menu items.

                static void DrawWindow(); // Draws the toolbar dock.
                inline static std::vector<MenuItem> menuItems; // A list of menu items.
        }; // The top bar of the editor (static).
    }

    class Application {
        public:

            virtual ~Application() = default; // Destructor.

            virtual void onInit() {}; // Called when the application is initialized.
            inline static bool quit; // Is the editor quitting?
    }; // A class for managing/hooking onto the internal editor.
}