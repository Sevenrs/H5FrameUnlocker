#include "FpsPatcher.hpp"

FpsPatcher::FpsPatcher(HANDLE hProcess, uintptr_t lpBaseOfDll)
{
    this->hProcess = hProcess;
    this->lpBaseOfDll = lpBaseOfDll;

    static uintptr_t addresses[] = {
        0x03425078,
        0x03425088,
        0x03425098
    };

    this->fpsAddresses = addresses;
    this->numAddresses = sizeof(addresses) / sizeof(addresses[0]);

}

/*
 * @author : Icseon
 * @brief  : Gets the FPS cap
 * @return : The FPS cap
 */
void FpsPatcher::GetFps()
{
    for (int i = 0; i < this->numAddresses; i++)
    {

        const uintptr_t fpsAddress = this->lpBaseOfDll + this->fpsAddresses[i];
        int fps;

        /* Read frame count from memory */
        ReadProcessMemory(this->hProcess, (LPVOID)fpsAddress, &fps, sizeof(fps), nullptr);

        /* Calculate the actual fps */
        int actualFps = 1000000 / fps;

        printf("[FpsPatcher::GetFps] Read fps from address %p: %d fps (%d)\n", (void*)fpsAddress, actualFps, fps);
        
    }
}

/*
 * @author : Icseon
 * @brief  : Sets the FPS cap
 * @param  : fps : The FPS cap to write to the game
 */
void FpsPatcher::SetFps(int fps)
{

    /* Calculate newFps */
    int newFps = (1000000 / fps);

    for (int i = 0; i < this->numAddresses; i++)
    {

        /* Determine the full address */
        const uintptr_t fpsAddress = this->lpBaseOfDll + this->fpsAddresses[i];

        /* Begin changing memory */
        DWORD oldProtect;
        VirtualProtectEx(this->hProcess, (LPVOID)fpsAddress, sizeof(newFps), PAGE_EXECUTE_READWRITE, &oldProtect);
        BOOL writeResult = WriteProcessMemory(this->hProcess, (LPVOID)fpsAddress, &newFps, sizeof(newFps), nullptr);
        VirtualProtectEx(this->hProcess, (LPVOID)fpsAddress, sizeof(newFps), oldProtect, &oldProtect);

        if (!writeResult)
        {
            DWORD error = GetLastError();
            printf("[FpsPatcher::SetFps] WriteProcessMemory failed with error %lu\n", error);
        }
        else
        {
            printf("[FpsPatcher::SetFps] Updated fps to %d at address 0x%p\n", fps, (void*)fpsAddress);
        }

    }

    printf("[FpsPatcher::SetFps] Updated fps to %d (%d)\n", fps, newFps);

}