////////////////////////////////////////////////////////////////////////////////////////
// winsys.h
//
// MS Win32Api windows managment system
////////////////////////////////////////////////////////////////////////////////////////

#ifndef _WINDOW_SYSTEM_
#define _WINDOW_SYSTEM_

#include <windows.h>

#define WINDOW_CLASS_NAME_SIZE 256

////////////////////////////////////////////////////////////////////////////////////////
// X windows managment system class
class CWindowSystem
{
public:
    CWindowSystem();
    ~CWindowSystem();
    
    int CreateDisplayWindow();
    bool ReleaseDisplayWindow();
    void ProcessEvents();
    
    static LRESULT CALLBACK DisplayWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    
    
protected:
    // Window handlers and structers
    HINSTANCE   m_hInstance;
    HWND        m_hWnd;
    HDC         m_hDC;
    WNDCLASSEX  m_WndClass;
    
    CHAR        m_strWidnowClassName[WINDOW_CLASS_NAME_SIZE];
    
private:
    void BreakProcess() {m_bRunning=false;}

    static CWindowSystem* GetWinSysInstance();
    static CWindowSystem *mWinSysInst;
    bool m_bRunning;
};
////////////////////////////////////////////////////////////////////////////////////////
#endif //_WINDOW_SYSTEM_