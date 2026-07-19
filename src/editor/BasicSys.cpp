#include <basicsys.hpp>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <unistd.h>
#endif

void OpenSourceFile(std::string directory, std::string fileName, std::string fileExtension)
{
    #if defined(_WIN32) || defined(_WIN64)
    ShellExecuteA(NULL, "open", (LPCSTR)(directory + fileName + fileExtension).c_str(), (LPCSTR)directory.c_str(), (LPCSTR)directory.c_str(), SW_HIDE);
    #else
    std::string command = "xdg-open \"" + directory + fileName + fileExtension + "\"";
    system(command.c_str());
    #endif
}

std::string GetPlatformLibs()
{
    #if defined(_WIN32) || defined(_WIN64)
    return "-lopengl32 -lgdi32 -lwinmm -lws2_32";
    #else
    return "-lGL -lm lpthread -ldl -lrt -lX11";
    #endif
}