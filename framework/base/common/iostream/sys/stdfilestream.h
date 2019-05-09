///////////////////////////////////////////////////////////////////////////////////////
//  stdfilestream.h
//
//  File input/output stream class using standard C functions
//  Created: 23-11-2011
//
///////////////////////////////////////////////////////////////////////////////////////

#ifndef __STD_FILE_STREAM_H__
#define __STD_FILE_STREAM_H__

#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////////////
class CStdFileStream : public IDataStream
{
public:
    CStdFileStream();
    virtual ~CStdFileStream();

    bool        Open(const char *filename, OpenMode mode);
    bool        Close();

    uint_t      Read(void *data, uint_t size);
    uint_t      Write(const void *data, uint_t size);

    bool        IsOpened();
    bool        Seek(isize_t offset, SeekMode pos);

    isize_t     GetPos();
    isize_t     GetSize();

    bool        IsEOS();

protected:
    FILE        *m_file;
    int_t       m_error;
    isize_t     m_size;
};

///////////////////////////////////////////////////////////////////////////////////////


#endif //__STD_FILE_STREAM_H__