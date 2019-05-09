///////////////////////////////////////////////////////////////////////////////////////
//  bufdatastream.h
//
//  Input/Output Buffer Data Stream Class
//  Created: 23-11-2011
//
///////////////////////////////////////////////////////////////////////////////////////

#ifndef __BUFFILESTREAM_H__
#define __BUFFILESTREAM_H__

#include "idatastream.h"

/*
///////////////////////////////////////////////////////////////////////////////////////
class CBufDataStream : public IDataStream;
{
public:
    CBufDataStream();
    virtual ~CBufDataStream();

    uint_t  Read(void *data, uint_t size);
    uint_t  Write(const void *data, uint_t size);

    bool    IsOpened();
    bool    Seek(isize_t offset, SeekMode mode);

    bool    Open(const char *filename, OpenMode mode);
    bool    Close();

    isize_t GetPos();
    isize_t GetSize();

    bool    IsEOS();

protected:

    int_t   m_buf_size;
    unsigned char *m_buffer;
    int_t   m_buf_pos;
    int_t   m_buf_fill;
};
*/

///////////////////////////////////////////////////////////////////////////////////////

#endif //__BUFFILESTREAM_H__