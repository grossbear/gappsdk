///////////////////////////////////////////////////////////////////////////////////////
// xwinsys.h
//
// X Windows managment system
///////////////////////////////////////////////////////////////////////////////////////

#include "../evtlistener.h"
#include "xwinsys.h"

///////////////////////////////////////////////////////////////////////////////////////
CWindowSystem::CWindowSystem(EventListener *listener):mEventListener(listener)
{
    mDisplay = XOpenDisplay(nullptr);
    
}
///////////////////////////////////////////////////////////////////////////////////////
CWindowSystem::~CWindowSystem()
{
    XDestroyWindow(mDisplay, mWindow);
    XCloseDisplay(mDisplay);
    mEventListener = nullptr;
}
///////////////////////////////////////////////////////////////////////////////////////
int CWindowSystem::CreateDisplayWindow()
{
    int screen = DefaultScreen(mDisplay);
    mWindow = XCreateSimpleWindow(mDisplay, RootWindow(mDisplay, screen), 10, 10, 660, 200, 1,
                                  BlackPixel(mDisplay, screen), WhitePixel(mDisplay, screen));
    XSelectInput(mDisplay, mWindow, ExposureMask | KeyPressMask);
    XMapWindow(mDisplay, mWindow);
    XStoreName(mDisplay, mWindow, "Experimental XWindow");
    mDelWndMsg = XInternAtom(mDisplay, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(mDisplay, mWindow, &mDelWndMsg, 1);
    
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////
bool CWindowSystem::ReleaseDisplayWindow()
{
    return false;
}
///////////////////////////////////////////////////////////////////////////////////////
void CWindowSystem::ProcessEvents()
{
    XEvent event;
    XNextEvent(mDisplay, &event);
    
    if (event.type == Expose)
    {
    }
    else if (event.type == KeyPress)
    {
        char buffer[128] = {0};
        KeySym keysym;
        int len = XLookupString(&event.xkey, buffer, sizeof(buffer), &keysym, NULL);
        if (keysym == XK_Escape) {
            mEventListener->OnQuit();
        }
    }
    else if ((event.type == ClientMessage) &&
             (static_cast<unsigned int>(event.xclient.data.l[0]) == mDelWndMsg))
    {
        mEventListener->OnClose();
    }
}
///////////////////////////////////////////////////////////////////////////////////////
             
             
             
             
             