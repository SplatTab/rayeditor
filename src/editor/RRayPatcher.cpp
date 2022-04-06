#include "rrayc.hpp"
#include "raypatcher.h"

void RRayPatcher::EditorInit(std::string projectPath) {
    RayPatcher::Context context;
    context.AddLibary((projectPath + "\\templibs\\test.dll").c_str());
    context.RunFunctions("Init");
}