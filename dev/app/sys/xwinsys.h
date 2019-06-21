///////////////////////////////////////////////////////////////////////////////////////
// xwinsys.h
//
// X Windows managment system
///////////////////////////////////////////////////////////////////////////////////////

#include <X11/Xlib.h>
#include <X11/Xutil.h>
//#include <X11/Xos.h>

class EventListener;

///////////////////////////////////////////////////////////////////////////////////////

// Window managment system #experimental version
class CWindowSystem
{
public:
    CWindowSystem(EventListener *listener);
    ~CWindowSystem();
    
    int CreateWindow();
    bool ReleaseWindow();
    void ProcessEvents();
    
protected:
    EventListener *mEventListener;
    
    Display *mDisplay;
    Window mWindow;
    Atom mDelWndMsg;
};

///////////////////////////////////////////////////////////////////////////////////////


