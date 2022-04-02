#include "rayeditor.hpp"

using namespace RayEditor;
using namespace Docks;

void Log::Info(std::string logText) {
    ConsoleDock::AddLog(LogItem{ "[Info]", logText, RAYWHITE, 0 });
}
void Log::Debug(std::string logText) {
    ConsoleDock::AddLog(LogItem{ "[Debug]", logText, SKYBLUE, 1 });
}

void Log::Warning(std::string logText) {
    ConsoleDock::AddLog(LogItem{ "[Warning]", logText, YELLOW, 2 });
}

void Log::Error(std::string logText) {
    ConsoleDock::AddLog(LogItem{ "[Error]", logText, RED, 3 });
}

void Log::TraceLog(int logType, const char* text, va_list args) {
    static char logText[2048] = { 0 };
    LogItem item;
    item.logType = logType;
    switch (logType)
    {
        default:            item.prefix = "[Log]"; item.logColor = GRAY; break;
        case LOG_TRACE:     item.prefix = "[Info]"; item.logColor = RAYWHITE; break;
        case LOG_INFO:      item.prefix = "[Info]"; item.logColor = RAYWHITE; break;
        case LOG_DEBUG:     item.prefix = "[Debug]"; item.logColor = SKYBLUE; break;
        case LOG_WARNING:   item.prefix = "[Warning]"; item.logColor = YELLOW; break;
        case LOG_ERROR:     item.prefix = "[Error]"; item.logColor = RED; break;
        case LOG_FATAL:     item.prefix = "[Fatal]"; item.logColor = PINK; break;
    }
    vsprintf(logText, text, args);
    item.logText += logText;
    ConsoleDock::AddLog(item);
}