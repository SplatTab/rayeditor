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
                static void TraceLog(int logType, const char* text, va_list args);
        };

        namespace RLCommonUtils {
            
            class StringUtils {
                public:

                    static char* stristr(const char* str1, const char* str2);
            };
        }
    }

    namespace Editor {
        class CurrentProject {
            static bool IsProjectLoaded();
            static const char* GetProjectDirectory();
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
                inline static char FilterText[512] = { 0 };
        };

        class AssetDock : public Dock {
            public:

                static void DrawWindow();

            private:

                inline static std::vector<std::string> files;
                inline static char FilterText[512] = { 0 };
        };

        class DockManager {
            public:

                static void DrawDocks();
        };
    }
}