#pragma once
#include <raylib.h>
#include <imgui.h>
#include <string>
#include <vector>
#include <functional>

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

    class Log {
        public:

            static void Info(std::string logText); // Logs a info message to the console dock.
            static void Debug(std::string logText); // Logs a debug message to the console dock.
            static void Warning(std::string logText); // Logs a warning message to the console dock.
            static void Error(std::string logText); // Logs a error message to the console dock.
            static void TraceLog(int logType, const char *text, va_list args); // Logs a message to the console dock.
    }; // A class for logging messages to the console dock for debugging purposes.

    class Project {
        public:

            static std::string GetProjectDirectory(); // Get's the active project directory.
            static bool SetProjectDirectory(const char *projectPath); // Set's the active project directory.
            inline static bool IsProjectLoaded; // Is a project loaded?

        private:

            inline static std::string projectDir; // The modifiable active project directory this should not be manually set.
    }; // A class for managing the current project and it's directories.

    class Application {
        public:

            inline static bool quit; // Is the editor quitting?
    }; // A class for managing the internal editor.

    namespace Docks {

        class ToolbarDock {
            public:

                static void DrawWindow(); // Draw's the toolbar dock.
        }; // The top bar of the editor (static).

        class ConsoleDock {
            public:

                static void DrawWindow(); // Draw's the console dock.
                static void AddLog(LogItem logItem); // Adds a log item to the console dock.

            private:

                inline static std::vector<LogItem> logItems; // A list of log items should not be modified manually.
                inline static char filterText[512] = { 0 }; // The text in the search bar to filter the log items with stristr.
        }; // The console dock display debugging information and logs (static).

        class Dock {
            public:

                virtual ~Dock() = default; // Destructor.

                virtual void StartWindow() {}; // Initialize you're dock window.
                virtual void DrawWindow() {}; // Draw you're dock window.
                virtual void CloseWindow() {}; // Unitialize you're dock window.
                bool isInitialized = false; // Is the dock initialized?
        }; // A base class for all docks.

        class AssetDock : public Dock {
            struct FileInfo {
                std::string fileName;
                Texture2D icon;
                bool isSelected = false;
                bool isDirectory = false;
            }; // A file info struct used to store file information.

            public:

                void StartWindow() override; // Initialize the asset dock window.
                void DrawWindow() override; // Draw's the asset dock.
                void CloseWindow() override; // Unitialize the asset dock.
                void RefreshFiles(); // Refreshes the files in the asset dock.

            private:

                std::vector<FileInfo> files; // A list of files in the asset dock.
                char filterText[512] = { 0 }; // The text in the search bar to filter the files with stristr.
        }; // A dock for navigating project files.

        class DockManager {
            public:

                static void UpdateDocks(); // Draw all open docks.
                static void CloseDocks(); // Unitialize all open docks.
                inline static std::vector<std::reference_wrapper<Dock>> activeDocks; // A list of active docks.
        }; // The dock manager handles all docks.
    }
}