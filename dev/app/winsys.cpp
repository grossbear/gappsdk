////////////////////////////////////////////////////////////////////////////////////////
// xwinsys.h
//
// X Windows managment system
////////////////////////////////////////////////////////////////////////////////////////
#include "winsys.h"
#include <stdio.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////////////                                                                                   
CWindowSystem::CWindowSystem():mWindow(0),mDelWndMsg(0)
{
    mDisplay = XOpenDisplay(nullptr);
}

////////////////////////////////////////////////////////////////////////////////////////
CWindowSystem::~CWindowSystem()
{
    if(mWindow) XDestroyWindow(mDisplay, mWindow);
    XCloseDisplay(mDisplay);
}

////////////////////////////////////////////////////////////////////////////////////////
int CWindowSystem::CreateDisplayWindow()
{
    int screen = DefaultScreen(mDisplay);
    mWindow = XCreateSimpleWindow(mDisplay, RootWindow(mDisplay, screen), 10, 10, 660, 200, 1,
                                  BlackPixel(mDisplay, screen), WhitePixel(mDisplay, screen));
    long mask = ExposureMask | KeyPressMask | SubstructureNotifyMask | StructureNotifyMask | PropertyChangeMask | ResizeRedirectMask;
    XSelectInput(mDisplay, mWindow, mask);
    XMapWindow(mDisplay, mWindow);
    XStoreName(mDisplay, mWindow, "Experimental XWindow");
    mDelWndMsg = XInternAtom(mDisplay, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(mDisplay, mWindow, &mDelWndMsg, 1);


    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
bool CWindowSystem::ReleaseDisplayWindow()
{
    if(mWindow) {
        XDestroyWindow(mDisplay, mWindow);
        mWindow = 0;
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////
void CWindowSystem::ProcessEvents()
{  
    while(1) {
       
        XEvent event;
        XNextEvent(mDisplay, &event);
        printf("event type = %d\n",event.type);

        switch(event.type) {
            case KeyPress:
            {
                //XComposeStatus status;
                KeySym keysym = NoSymbol;
                char buffer[32] = {0};

                int lookup_length = XLookupString(&event.xkey, buffer, sizeof(buffer)-1, &keysym, nullptr);
                printf("keysym = %zu, len = %d\n",keysym, lookup_length);
                if(keysym == XK_Escape)
                    return ;
            }
            break;

            case Expose:
            {
                printf("event.xexpose.count = %d\n",event.xexpose.count);
                const char* s1 = "X11 test app under Linux";
                int screen = DefaultScreen(mDisplay);
                XDrawString(mDisplay, mWindow, DefaultGC(mDisplay, screen), 10, 20, s1, strlen(s1));
            }
            break;

            case ResizeRequest:
                printf("Resize request\n");
            break;

            case CreateNotify:
                printf("CreateNotify\n");
            break;

            case ClientMessage:
            {
                Atom client_msg = static_cast<unsigned int>(event.xclient.data.l[0]);
                if(client_msg == mDelWndMsg)
                    return ;        
            }
            
            break;
        }

    }
}

////////////////////////////////////////////////////////////////////////////////////////
