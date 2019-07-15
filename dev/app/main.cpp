#include "winsys.h"

int main(int argc, char *argv[])
{
    CWindowSystem *winsys = new CWindowSystem();
    winsys->CreateDisplayWindow();
    winsys->ProcessEvents();
    delete (winsys);
    return 0;   
}