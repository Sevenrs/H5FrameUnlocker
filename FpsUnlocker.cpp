#include "FpsUnlocker.hpp"

FpsUnlocker::FpsUnlocker(HANDLE hProcess, uintptr_t lpBaseOfDll)
{
    this->hProcess = hProcess;
    this->lpBaseOfDll = lpBaseOfDll;

    static uintptr_t addresses[] = {
        0x03425078,
        0x03425088,
        0x03425098
    };

    this->fpsAddresses = addresses;

}

/*
 * @author : Icseon
 * @brief  : Gets the FPS cap
 * @return : The FPS cap
 */
int FpsUnlocker::GetFps()
{

    const uintptr_t fpsAddress = this->lpBaseOfDll + this->fpsAddresses[0];
    int fps;

    /* Read frame count from memory */
    ReadProcessMemory(this->hProcess, (LPVOID)fpsAddress, &fps, sizeof(fps), nullptr);

    /* Calculate the actual fps */
    int actualFps = 1000000 / fps;

    printf("[FpsUnlocker::GetFps] Read %d fps\n", fps);

    return actualFps;

}

/*
 * @author : Icseon
 * @brief  : Sets the FPS cap
 * @param  : fps : The FPS cap to write to the game
 */
void FpsUnlocker::SetFps(int fps)
{

    /* Compute number of addresses */
    int numAddresses = sizeof(this->fpsAddresses) / sizeof(this->fpsAddresses[0]);

    /* Calculate newFps */
    int newFps = fps * 1000000;

    for (int i = 0; i < numAddresses; i++)
    {
        WriteProcessMemory(this->hProcess, (LPVOID)(fpsAddresses[i]), &newFps, sizeof(newFps), nullptr);
    }

    printf("[FpsUnlocker::SetFps] Updated fps to %d\n", fps);

}