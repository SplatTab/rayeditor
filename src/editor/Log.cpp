#include "rayeditor.hpp"

using namespace RayEditor;
using Docks::Console;

///<summary>
/// Logs a info message to the editor log.
///</summary>
void Log::Info(std::string logText)
{
    Console::AddLog(LogItem{ "[Info]", logText, RAYWHITE, 0 });
}

///<summary>
/// Logs a debug message to the editor log.
///</summary>
void Log::Debug(std::string logText)
{
    Console::AddLog(LogItem{ "[Debug]", logText, SKYBLUE, 1 });
}

///<summary>
/// Logs a warning message to the editor log.
///</summary>
void Log::Warning(std::string logText)
{
    Console::AddLog(LogItem{ "[Warning]", logText, YELLOW, 2 });
}

///<summary>
/// Logs a error message to the editor log.
///</summary>
void Log::Error(std::string logText)
{
    Console::AddLog(LogItem{ "[Error]", logText, RED, 3 });
}

///<summary>
/// Logs a message to the editor log.
///</summary>
void Log::TraceLog(int logType, const char* text, va_list args)
{
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
    Console::AddLog(item);
}