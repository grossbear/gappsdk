////////////////////////////////////////////////////////////////////////////////////////
// winsys.h
//
// MS Win32Api windows managment system
////////////////////////////////////////////////////////////////////////////////////////

#include <memory.h>
#include <stdio.h>
#include "winsys.h"

CWindowSystem* CWindowSystem::mWinSysInst = NULL;

////////////////////////////////////////////////////////////////////////////////////////
CWindowSystem::CWindowSystem()
{
    m_hWnd = NULL;
    m_hDC = NULL;
    memset(&m_WndClass,0, sizeof(WNDCLASSEX));
    memset(m_strWidnowClassName,0,sizeof(CHAR)*WINDOW_CLASS_NAME_SIZE);
    m_hInstance = GetModuleHandle(NULL);
    m_bRunning = true;
    
    mWinSysInst = this;
}
////////////////////////////////////////////////////////////////////////////////////////
CWindowSystem::~CWindowSystem()
{
    ReleaseDisplayWindow();
}
////////////////////////////////////////////////////////////////////////////////////////
int CWindowSystem::CreateDisplayWindow()
{
    WNDCLASSEX wndclass;
    memset(&wndclass,0,sizeof(WNDCLASSEX));

    wndclass.cbSize = sizeof(WNDCLASSEX);                               // Size of structure
    wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;                // Redraw On Size, And Own DC For Window.
    wndclass.lpfnWndProc = (WNDPROC)CWindowSystem::DisplayWinProc;      // WndProc Handles Messages
    wndclass.cbClsExtra = 0;                            // No Extra Window Data
    wndclass.cbWndExtra = 0;                            // No Extra Window Data
    wndclass.hInstance = m_hInstance;                   // Set The Instance
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);   // Load The Default Icon
    wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);      // Load The Arrow Pointer
    wndclass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;  // White Background
    wndclass.lpszMenuName = NULL;					    // We Don't Want A Menu
    wndclass.lpszClassName = "WindowClassName";         // Set The Class Name
    wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // Load small icon

    RegisterClassEx(&wndclass);
    
    // Window styles
    DWORD dwStyle   = WS_CAPTION | WS_SYSMENU | WS_OVERLAPPEDWINDOW; //WS_MINIMIZEBOX;
    DWORD dwexStyle = WS_EX_APPWINDOW;
    
    // Create the window
    m_hWnd = CreateWindowEx(dwexStyle,  // Extended Style For The Window
        "WindowClassName",              // Class Name
        "AppName",                      // Window Title
        dwStyle,                        // Required Window Style
        CW_USEDEFAULT, CW_USEDEFAULT,   // Window Position
        640, 480,                       // Window width and height
        NULL,                           // No Parent Window
        NULL,                           // No Menu
        m_hInstance,                    // Instance
        NULL);
        
    //Setting Window Params
    ShowWindow(m_hWnd,SW_SHOW);
    SetForegroundWindow(m_hWnd);
    SetFocus(m_hWnd);
    
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
bool CWindowSystem::ReleaseDisplayWindow()
{
    if(m_hWnd) {
        DestroyWindow(m_hWnd);
        UnregisterClass("WindowClassName",m_hInstance);
        return true;
    }
    
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////
void CWindowSystem::ProcessEvents()
{
    while(m_bRunning)
    {
        MSG msg;
        if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))    // Is There A Message Waiting?
        {
            TranslateMessage(&msg);                 // Translate The Message
            DispatchMessage(&msg);                  // Dispatch The Message
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////
CWindowSystem* CWindowSystem::GetWinSysInstance()
{
    return mWinSysInst;
}
////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK CWindowSystem::DisplayWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    CWindowSystem *winsys = CWindowSystem::GetWinSysInstance();
    switch(msg)
    {
    case WM_CLOSE:
        printf("WM_CLOSE message\n");
        winsys->BreakProcess();
        break;

    case WM_QUIT:
        printf("WM_QUIT message\n");
        winsys->BreakProcess();
        break;    
    }
    
    //Pass all unhandled messages to DefWindowProc
    return DefWindowProc(hWnd,msg,wParam,lParam);
}
////////////////////////////////////////////////////////////////////////////////////////