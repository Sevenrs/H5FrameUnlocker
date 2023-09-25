#include "MemoryUtil.cpp"
#include "FpsPatcher.cpp"

int main(int argc, char* argv[])
{

    if (argc < 2)
    {
        printf("[Main] Please specify a FPS cap through the command line arguments. Read README.md for more information. Aborting.\n");
        return 1;
    }

    /* Create new MemoryUtil instance */
    MemoryUtil* MemoryUtilities = new MemoryUtil();

    /* Open the game process */
    HANDLE hGameProcess = MemoryUtilities->OpenProcessByName("halo5forge.exe");

    /* Check if the process could be opened */
    if (!hGameProcess)
    {
        printf("[Main] Failed to find game process. Please run the game before running this\n");
        return 1;
    }

    /* Retrieve base address of the game process */
    uintptr_t lpBaseOfDll = MemoryUtilities->GetExecutableBaseAddress(hGameProcess);

    /* Create new FpsPatcher instance */
    FpsPatcher* FramePatcher = new FpsPatcher(hGameProcess, lpBaseOfDll);

    /* Get current FPS cap and print to console */
    FramePatcher->GetFps();

    /* Set new frame fap */
    FramePatcher->SetFps(atoi(argv[1]));

    return 0;

}