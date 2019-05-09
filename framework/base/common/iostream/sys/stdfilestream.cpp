///////////////////////////////////////////////////////////////////////////////////////
//  stdfilestream.cpp
//
//  File input/output stream class using standard C functions
//  Created: 23-11-2011
//
///////////////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "../filestream.h"


///////////////////////////////////////////////////////////////////////////////////////
CStdFileStream::CStdFileStream():m_file(NULL),m_error(0),m_size(0){}

///////////////////////////////////////////////////////////////////////////////////////
CStdFileStream::~CStdFileStream()
{
    Close();
}

///////////////////////////////////////////////////////////////////////////////////////
bool CStdFileStream::Open(const char *filename, OpenMode mode)
{
    if(filename == NULL)
        return (bool)false;

    if(m_file != NULL)
        return (bool)false;

    static const char mode_tab[][4] = {"rb","wb+","wb+","ab","ab+"};

    m_file = fopen(filename,&mode_tab[mode][0]);
    if(m_file == NULL)
    {
        //m_error = -1;
        return (bool)false;
    }

    return (bool)true;
}

///////////////////////////////////////////////////////////////////////////////////////
bool CStdFileStream::Close()
{
    if(!m_file)
        return false;

    int error = fclose(m_file);
    m_file = NULL;
    m_size = 0;
    m_error = 0;
    return (bool)(error == 0);
}

///////////////////////////////////////////////////////////////////////////////////////
uint_t CStdFileStream::Read(void *data, uint_t size)
{
    if(m_file == NULL)
        return -1;

    size_t readed = fread(data,size,1,m_file);

    return (uint_t)readed;
}

///////////////////////////////////////////////////////////////////////////////////////
uint_t CStdFileStream::Write(const void *data, uint_t size)
{
    if(m_file == NULL)
        return -1;
    size_t written = fwrite(data,size,1,m_file);

    return (uint_t)written;
}

///////////////////////////////////////////////////////////////////////////////////////
bool CStdFileStream::IsOpened()
{
    return (bool)(m_file != NULL);
}

///////////////////////////////////////////////////////////////////////////////////////
bool CStdFileStream::Seek(isize_t offset, SeekMode mode)
{
    int error = 0;
    static const int mode_tab[] = {SEEK_SET,SEEK_CUR,SEEK_END};
#ifdef SIZE_INT_64
    error = _fseeki64(m_file,(__int64)offset,mode_tab[mode]);
#else
    error = fseek(m_file,offset,mode_tab[mode]);
#endif
    return (bool)(error==0);
}

///////////////////////////////////////////////////////////////////////////////////////
isize_t CStdFileStream::GetPos()
{
    if(m_file == NULL)
        return -1;

    isize_t pos = -1;
#ifdef SIZE_INT_64
    pos = _ftelli64(m_file);
#else
    pos = ftell(m_file);
#endif
    return pos;
}

///////////////////////////////////////////////////////////////////////////////////////
isize_t CStdFileStream::GetSize()
{
    if(m_file == NULL)
        return -1;

    if(m_size == 0)
    {
        isize_t currpos = GetPos();
        Seek(0,seek_end);
        m_size = GetPos();
        Seek(currpos,seek_set);

    }

    return m_size;
}

///////////////////////////////////////////////////////////////////////////////////////
bool CStdFileStream::IsEOS()
{
    if(m_file == NULL)
        return (bool)false;
    int eof = feof(m_file);
    return (bool)(eof==0);
}

///////////////////////////////////////////////////////////////////////////////////////