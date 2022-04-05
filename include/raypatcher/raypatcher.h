/**********************************************************************************************
 * RayPatcher is a library that allows you to load compile and execute libary's dynamically at runtime.
 * LICENSE: ZLIB
 * Copyright (c) 2022 (SplatTab)
**********************************************************************************************/

#pragma once
#include "raybehavior.h"
#include "rpdll.h"
#include <string>
#include <vector>

namespace RayPatcher {
    class Context {
        public:

            bool AddLibary(const char* path);
            void RunFunctions(const char* functionName);
            void Destroy();

        private:

            std::vector<HMODULE> m_loadedLibs;
    };
}