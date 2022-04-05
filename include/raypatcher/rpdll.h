/**********************************************************************************************
 * RayPatcher Dynamic Linking Loader
 * LICENSE: ZLIB
 * Copyright (c) 2022 (SplatTab)
**********************************************************************************************/

#pragma once
#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class RPDLL
{
    public:

        static HMODULE LoadLibary(const char* path);
        static bool RunFunction(const char* functionName, HMODULE lib);

};