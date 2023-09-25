#pragma once

#include <windows.h>

class FpsUnlocker {

    private:

        /* Game process */
        HANDLE hProcess;

        /* Game base address */
        uintptr_t lpBaseOfDll;

        /* Fps addresses */
        uintptr_t* fpsAddresses;

    public:

        /* Constructor */
        FpsUnlocker(HANDLE hProcess, uintptr_t lpBaseOfDll);

        /* Gets the FPS */
        int GetFps();

        /* Sets the FPS */
        void SetFps(int fps);

};