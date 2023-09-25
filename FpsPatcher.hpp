#pragma once

#include <windows.h>

class FpsPatcher {

    private:

        /* Game process */
        HANDLE hProcess;

        /* Game base address */
        uintptr_t lpBaseOfDll;

        /* Fps addresses */
        uintptr_t* fpsAddresses;
        int numAddresses;

    public:

        /* Constructor */
        FpsPatcher(HANDLE hProcess, uintptr_t lpBaseOfDll);

        /* Gets the FPS */
        void GetFps();

        /* Sets the FPS */
        void SetFps(int fps);

};