///////////////////////////////////////////////////////////////////////////////////////
// winsys.h
//
// Windows managment system
///////////////////////////////////////////////////////////////////////////////////////

#ifndef __WINSYS_H__
#define __WINSYS_H__

#ifdef WIN32
#include "sys/win32sys.h"
#else
#include "sys/xwinsys.h"
#endif

#endif //__WINSYS_H__