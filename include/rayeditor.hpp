#pragma once
#include <raylib.h>
#include <imgui.h>
#include <string>
#include <vector>

namespace RayEditor {

    struct LogItem {
        std::string prefix;
        std::string logText;
        Color logColor;
        int logType;
    };

    namespace Utility {
        class Conversion {
            public:

                static ImVec4 RayColorToImguiColor(Color color);
        };

        class Log {
            public:

                static void Info(std::string logText);
                static void Debug(std::string);
                static void Warning(std::string);
                static void Error(std::string);
                static void TraceLog(int logType, const char *text, va_list args);
        };

        namespace RLCommonUtils {

            class StringUtils {
                public:

                    static char *stristr(const char *str1, const char * str2);
            };
        }
    }

    namespace Editor {
        #define EDITOR_VERSION "0.5.0"

        class Project {
            public:

                static std::string GetProjectDirectory();
                static bool SetProjectDirectory(const char *projectPath);
                inline static bool IsProjectLoaded;

            private:
                inline static std::string projectDir;
        };

        class Application {
            public:

                inline static bool quit;
        };
    }

    namespace Docks {
        class Dock {
            public:

                static void DrawWindow();
        };

        class ConsoleDock : public Dock {
            public:

                static void DrawWindow();
                static void AddLog(LogItem logItem);

            private:

                inline static std::vector<LogItem> logItems;
                inline static char filterText[512] = { 0 };
        };

        class AssetDock : public Dock {
            struct FileInfo {
                std::string fileName;
                Texture2D icon;
                bool isSelected;
                bool isDirectory;
            };

            public:

                static void DrawWindow();
                static void CloseWindow();
                static void RefreshFiles();

            private:

                inline static std::vector<FileInfo> files;
                inline static char filterText[512] = { 0 };
        };

        class ToolbarDock : public Dock {
            public:

                static void DrawWindow();
        };

        class DockManager {
            public:

                static void DrawDocks();
                static void CloseDocks();
        };
    }
}