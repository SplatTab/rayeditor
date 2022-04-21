#include <basicsys.hpp>

#ifdef __WIN32__
#include <windows.h>
#elif __linux__
#include <unistd.h>
#endif

void OpenSourceFile(std::string directory, std::string fileName, std::string fileExtension)
{
    #ifdef __WIN32__
    ShellExecuteA(NULL, "open", (LPCSTR)(directory + fileName + fileExtension).c_str(), (LPCSTR)directory.c_str(), (LPCSTR)directory.c_str(), SW_HIDE);
    #elif __linux__
    execl("code", (currentProjectDirectory + activeRelativeLocation + "\\ " + currentProjectDirectory + activeRelativeLocation + "\\" + fileName + fileExtension).c_str())
    #endif
}