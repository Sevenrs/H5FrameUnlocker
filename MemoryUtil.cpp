#include "MemoryUtil.hpp"

/*
 * @author : Icseon
 * @brief  : Opens a process by its process name
 * @param  : processName: Name of the process we wish to open
 * @return : Handle of the opened process
 */
HANDLE MemoryUtil::OpenProcessByName(const char* processName)
{
    
    /* DWORD storing open processes */
    DWORD processes[1024];

    /* DWORD storing number of bytes returned from EnumProcesses */
    DWORD bytesReturned;

    /* Enumerate through all open processes */
    if (!EnumProcesses(processes, sizeof(processes), &bytesReturned))
    {
        printf("[MemoryUtil::OpenProcessByName] EnumProcesses has failed\n");
        return nullptr;
    }

    /* Number of open processes - computed from the number of bytes returned */
    DWORD numProcesses = bytesReturned / sizeof(DWORD);

    /* Loop through every process until we find the relevant process */
    for (DWORD i = 0; i < numProcesses; i++)
    {

        /* Open process with read and write access */
        DWORD processId = processes[i];
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

        if (hProcess)
        {
            
            /* Initialize buffer for the process name (max length of 240) */
            char processNameBuffer[MAX_PATH];

            /* Retrieve process name */
            if (GetModuleBaseName(hProcess, NULL, processNameBuffer, sizeof(processNameBuffer)))
            {

                /* If the process name matches our expected process name, return the process handle */
                if (strcmp(processNameBuffer, processName) == 0)
                {
                    return hProcess;
                }

                CloseHandle(hProcess);

            }

        }

    }

    return nullptr;

}

/*
 * @author : Icseon
 * @brief  : Retrieves the base address of a process
 * @param  : hProcess: Process handle we wish to retrieve the base address of
 * @return : Module base address
 */
uintptr_t MemoryUtil::GetExecutableBaseAddress(HANDLE hProcess)
{
    HMODULE hModule;
    DWORD cbNeeded;

    if (EnumProcessModules(hProcess, &hModule, sizeof(hModule), &cbNeeded))
    {

        MODULEINFO moduleInfo;

        if (GetModuleInformation(hProcess, hModule, &moduleInfo, sizeof(MODULEINFO)))
        {
            return (uintptr_t)moduleInfo.lpBaseOfDll;
        }

    }

    return 0;
    
}