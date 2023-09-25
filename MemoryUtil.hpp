#pragma once

#include <windows.h>
#include <cstdio>
#include <psapi.h>

class MemoryUtil {

    public:

        /* Process opening */
        HANDLE OpenProcessByName(const char* processName);

        /* Method to retrieve process base address */
        uintptr_t GetExecutableBaseAddress(HANDLE hProcess);
        
};