#include "MemoryUtil.cpp"
#include "FpsUnlocker.cpp"

int main(int argc, char* argv[])
{

    /* Create new MemoryUtil instance */
    MemoryUtil* MemoryUtilities = new MemoryUtil();

    /* Open the game process */
    HANDLE hGameProcess = MemoryUtilities->OpenProcessByName("halo5forge.exe");

    /* Check if the process could be opened */
    if (!hGameProcess)
    {
        printf("[Main] Failed to find game process. Please run the game before running this");
        return 1;
    }

    /* Retrieve base address of the game process */
    uintptr_t lpBaseOfDll = MemoryUtilities->GetExecutableBaseAddress(hGameProcess);

    /* Create new FpsUnlocker instance */
    FpsUnlocker* FrameUnlocker = new FpsUnlocker(hGameProcess, lpBaseOfDll);

    /* Get current FPS cap and print to console */
    FrameUnlocker->GetFps();

    /* Set new frame fap */
    FrameUnlocker->SetFps(240);

    return 0;

}