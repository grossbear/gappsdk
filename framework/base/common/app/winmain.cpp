///////////////////////////////////////////////////////////////////////////////////////
// winmain.cpp
//
// Win32 API programme entry point
///////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <stdio.h>

#define WINMAIN WinMain


///////////////////////////////////////////////////////////////////////////////////////
INT WINAPI WINMAIN(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
{
    printf("WinMain\n");
    printf("cmdline: %s\n",lpCmdLine);
    printf("showcmd: %d\n",nShowCmd);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////