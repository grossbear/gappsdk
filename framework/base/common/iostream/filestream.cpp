///////////////////////////////////////////////////////////////////////////////////////
//  FileStream.cpp
//
//  Input/Output file stream class
//  Created: 23-11-2011
//
///////////////////////////////////////////////////////////////////////////////////////


#ifdef WIN32
#include "sys/win32filestream.cpp"
#else 
#include "sys/stdfilestream.cpp"
#endif