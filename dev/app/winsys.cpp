////////////////////////////////////////////////////////////////////////////////////////
// xwinsys.h
//
// X Windows managment system
////////////////////////////////////////////////////////////////////////////////////////
#include "winsys.h"
#include <stdio.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////////////                                                                                   
CWindowSystem::CWindowSystem():mXWindow(0),mXRootWindow(0)//,mDelWndMsg(0)
{
    mXDisplay = XOpenDisplay(NULL);
    int xscreen = DefaultScreen(mXDisplay);
    mXRootWindow = RootWindow(mXDisplay,xscreen);
    mXVisual = DefaultVisual(mXDisplay, xscreen);

/*
XVisualInfo visual_template;
XVisualInfo *visual_list;
XVisualInfo vinfo;

visual_template.screen = DefaultScreen(x_display);
visual_list = XGetVisualInfo(x_display, VisualScreenMask, &visual_template, &nxvisuals);

XMatchVisualInfo(x_display, XDefaultScreen(x_display), 32, TrueColor, &vinfo)
*/

    printf("xdisplay = %p, xscreen = %d, xrootwindow = %zu, xvisual = %p\n", mXDisplay, xscreen, mXRootWindow, mXVisual);
}

////////////////////////////////////////////////////////////////////////////////////////
CWindowSystem::~CWindowSystem()
{
    if(mXWindow) XDestroyWindow(mXDisplay, mXWindow);
    XCloseDisplay(mXDisplay);
}

////////////////////////////////////////////////////////////////////////////////////////
int CWindowSystem::CreateDisplayWindow()
{
    // Create a colormap - only needed on some X clients, eg. IRIX 
    Colormap colormap = XCreateColormap(mXDisplay,mXRootWindow,mXVisual,AllocNone);

    int screen = DefaultScreen(mXDisplay);

    XSetWindowAttributes xattributes = {0};
    xattributes.colormap = colormap;
    xattributes.background_pixel = WhitePixel(mXDisplay, screen);
    xattributes.event_mask = StructureNotifyMask | SubstructureNotifyMask |
        PropertyChangeMask |
        ResizeRedirectMask |
		EnterWindowMask |
		LeaveWindowMask |
		ExposureMask |
		ButtonPressMask |
		ButtonReleaseMask |
		OwnerGrabButtonMask |
		KeyPressMask |
		KeyReleaseMask;
    

    unsigned long attr_mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;
    int width = 600;
    int height = 200;
    int x = 100, y = 100;
    mXWindow = XCreateWindow(mXDisplay, mXRootWindow, x,y,width,height, 0, CopyFromParent, InputOutput, mXVisual, attr_mask, &xattributes);

    //long mask = ExposureMask | KeyPressMask | SubstructureNotifyMask | StructureNotifyMask | PropertyChangeMask | ResizeRedirectMask;
    //XSelectInput(mDisplay, mWindow, mask);

    XMapWindow(mXDisplay, mXWindow);
    XStoreName(mXDisplay, mXWindow, "Experimental XWindow");

	if ((mDelWndMsg = XInternAtom(mXDisplay, "WM_DELETE_WINDOW", 0)) != None) {
		XSetWMProtocols(mXDisplay, mXWindow, &mDelWndMsg, 1);
	}

    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
bool CWindowSystem::ReleaseDisplayWindow()
{
    if(mXWindow) {
        XDestroyWindow(mXDisplay, mXWindow);
        mXWindow = 0;
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////
void CWindowSystem::ProcessEvents()
{  
     while(1) {
       
        XEvent event;
        XNextEvent(mXDisplay, &event);
        printf("event type = %d\n",event.type);

        switch(event.type) {
            case KeyPress:
            {
                //XComposeStatus status;
                KeySym keysym = NoSymbol;
                char buffer[32] = {0};

                int lookup_length = XLookupString(&event.xkey, buffer, sizeof(buffer)-1, &keysym, NULL);
                //printf("keysym = %zu, len = %d\n",keysym, lookup_length);
                if(keysym == XK_Escape)
                    return ;
            }
            break;

            case Expose:
            {
                //printf("event.xexpose.count = %d\n",event.xexpose.count);
                const char* s1 = "X11 test app under Linux";
                int screen = DefaultScreen(mXDisplay);
                XDrawString(mXDisplay, mXWindow, DefaultGC(mXDisplay, screen), 10, 20, s1, strlen(s1));
            }
            break;

            case ResizeRequest:
                printf("Resize request, width = %d, height = %d\n",event.xresizerequest.width,event.xresizerequest.height);
            break;

            case CreateNotify:
                printf("CreateNotify\n");
            break;

            case ConfigureNotify:
                //printf("ConfigureNotify\n");
                //printf("width = %d, height = %d\n",event.xconfigure.width, event.xconfigure.height);
                
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
