// note: on dll inject there is no console == no printf
#include <windows.h>
#include <stdio.h>
#include <unistd.h>

// #define EXPORT __declspec(dllexport)
// EXPORT void testfunc(){
//     printf("test");
//     fflush(stdout);
// }

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved){
    FILE * fp;
    fp = fopen ("C:\\Users\\wsam\\Documents\\Hacked.txt","w");
    fprintf (fp, "Hacked\n");
    fclose (fp);

    while(1){
        // printf("HACKED\n");
        // fflush(stdout);
        // sleep(1);
    }
}