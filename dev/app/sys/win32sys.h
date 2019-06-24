///////////////////////////////////////////////////////////////////////////////////////
// win32sys.h
//
// Win32 windows managment system
///////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "../evtlistener.h"

class EventListener;

///////////////////////////////////////////////////////////////////////////////////////

// Win32 managment system #experimental version
class CWindowSystem
{
public:
    CWindowSystem(EventListener *listener);
    ~CWindowSystem();
    
    int CreateDisplayWindow();
    bool ReleaseDisplayWindow();
    void ProcessEvents();
    
    static LRESULT CALLBACK DisplayWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    
protected:
    static EventListener *mEventListener;
    
    HINSTANCE m_hInstance;
    HWND m_hWnd;
    HDC  m_hDC;
    
    
};

///////////////////////////////////////////////////////////////////////////////////////