/////////////////////////////////////////////////////////////////////////////////////////////
// stopwatch.cpp
//
// Time measure stop watch classes defintions
/////////////////////////////////////////////////////////////////////////////////////////////

#include "stopwatch.h"
#include <stdio.h>
#include <iostream>

#ifdef WINTIME_MEASURE
#include <MMSystem.h>
#pragma comment (lib, "winmm.lib")
#endif //WINTIME_MEASURE

/////////////////////////////////////////////////////////////////////////////////////////////
#if defined WINTIME_MEASURE
/////////////////////////////////////////////////////////////////////////////////////////////
inline unsigned int GetStopWatchTime()
{
    return timeGetTime();
}

/////////////////////////////////////////////////////////////////////////////////////////////
inline float ConvertClockTimeToFloat(DWORD time_val)
{
    return float(time_val) / 1000.0f;
}
/////////////////////////////////////////////////////////////////////////////////////////////
inline unsigned int ConvertClockTimeToUInt(DWORD time_val)
{
    return (unsigned int) time_val;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Stop watch time measure class
CStopWatch::CStopWatch(bool bactivate):
m_StartTime(0),
m_CurrTime(0),
m_Paused(true)
{
    timeBeginPeriod(1);
    
    Reset();
    if(bactivate) Start();
}
/////////////////////////////////////////////////////////////////////////////////////////////
CStopWatch::~CStopWatch()
{
    timeEndPeriod(1);
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CStopWatch::Start()
{
    if(!IsPaused()) return ;

    m_Paused = false;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CStopWatch::Stop()
{
    if(IsPaused()) return ;

    m_CurrTime = GetStopWatchTime();
    m_Paused = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CStopWatch::Reset()
{
    m_StartTime = GetStopWatchTime();
    m_CurrTime = m_StartTime;
}
/////////////////////////////////////////////////////////////////////////////////////////////
bool CStopWatch::IsPaused() const
{
    return m_Paused;
}

/////////////////////////////////////////////////////////////////////////////////////////////
float CStopWatch::GetTime()
{
    if(m_Paused)
    {
        DWORD timediff = m_CurrTime - m_StartTime;
        float ftime = ConvertClockTimeToFloat(timediff);
        
        return ftime;
    }
    
    DWORD currtime = GetStopWatchTime();
    DWORD timediff = currtime - m_StartTime;
    float ftime = ConvertClockTimeToFloat(timediff);
    
    return ftime;
}
/////////////////////////////////////////////////////////////////////////////////////////////
unsigned int CStopWatch::GetTicks()
{
    if(m_Paused)
    {
        DWORD timediff = m_CurrTime - m_StartTime;
        unsigned int uitime = ConvertClockTimeToUInt(timediff);
        return uitime;
    }
    
    DWORD currtime = GetStopWatchTime();
    DWORD timediff = currtime - m_StartTime;
    unsigned int uitime = ConvertClockTimeToUInt(timediff);
  
    return uitime;
}
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
#elif defined STDCHRONOLIB_TIME_MEASURE
/////////////////////////////////////////////////////////////////////////////////////////////
inline std::chrono::steady_clock::time_point GetStopWatchTime()
{
    return std::chrono::steady_clock::now();
}


/////////////////////////////////////////////////////////////////////////////////////////////
// Stop watch time measure class
CStopWatch::CStopWatch(bool bactivate):
m_Paused(true)
{
    Reset();
    if(bactivate) Start();
}
/////////////////////////////////////////////////////////////////////////////////////////////
CStopWatch::~CStopWatch()
{

}
/////////////////////////////////////////////////////////////////////////////////////////////
void CStopWatch::Start()
{
    if(!IsPaused()) return ;

    m_Paused = false;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CStopWatch::Stop()
{
    if(IsPaused()) return ;

    m_CurrTime = GetStopWatchTime();
    m_Paused = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CStopWatch::Reset()
{
    m_StartTime = GetStopWatchTime();
    m_CurrTime = m_StartTime;
}
/////////////////////////////////////////////////////////////////////////////////////////////
bool CStopWatch::IsPaused() const
{
    return m_Paused;
}

/////////////////////////////////////////////////////////////////////////////////////////////
float CStopWatch::GetTime()
{
    if(m_Paused)
    {
        std::chrono::duration<float> fsec = m_CurrTime - m_StartTime;
        std::chrono::milliseconds dsec = std::chrono::duration_cast<std::chrono::milliseconds>(fsec);
        
        return (float)dsec.count() / 1000.f;
    }
    
    std::chrono::steady_clock::time_point currtime = GetStopWatchTime();
    std::chrono::duration<float> fsec = currtime - m_StartTime;
    std::chrono::milliseconds dsec = std::chrono::duration_cast<std::chrono::milliseconds>(fsec);
    
    return fsec.count() / 1000.f;
}
/////////////////////////////////////////////////////////////////////////////////////////////
unsigned int CStopWatch::GetTicks()
{
    if(m_Paused)
    {
        std::chrono::duration<float> fsec = m_CurrTime - m_StartTime;
        std::chrono::milliseconds dsec = std::chrono::duration_cast<std::chrono::milliseconds>(fsec);
        
        return (unsigned int)dsec.count();
    }
    
    std::chrono::steady_clock::time_point currtime = GetStopWatchTime();
    std::chrono::duration<float> fsec = currtime - m_StartTime;
    std::chrono::milliseconds dsec = std::chrono::duration_cast<std::chrono::milliseconds>(fsec);
    
    return (unsigned int) fsec.count();
}
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
#else // Use C time library
/////////////////////////////////////////////////////////////////////////////////////////////
inline clock_t GetStopWatchTime()
{
    return clock();
}

/////////////////////////////////////////////////////////////////////////////////////////////
inline float ConvertClockTimeToFloat(clock_t time_val)
{
    return (float) time_val / CLOCKS_PER_SEC;
}
/////////////////////////////////////////////////////////////////////////////////////////////
inline unsigned int ConvertClockTimeToUInt(clock_t time_val)
{
    return ((unsigned int) time_val) / 1000;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Stop watch time measure class
CStopWatch::CStopWatch(bool bactivate):
m_StartTime(0),
m_CurrTime(0),
m_Paused(true)
{
    Reset();
    if(bactivate) Start();
}
/////////////////////////////////////////////////////////////////////////////////////////////
CStopWatch::~CStopWatch()
{
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CStopWatch::Start()
{
    if(!IsPaused()) return ;

    m_Paused = false;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CStopWatch::Stop()
{
    if(IsPaused()) return ;

    m_CurrTime = GetStopWatchTime();
    m_Paused = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CStopWatch::Reset()
{
    m_StartTime = GetStopWatchTime();
    m_CurrTime = m_StartTime;
}
/////////////////////////////////////////////////////////////////////////////////////////////
bool CStopWatch::IsPaused() const
{
    return m_Paused;
}

/////////////////////////////////////////////////////////////////////////////////////////////
float CStopWatch::GetTime()
{
    if(m_Paused)
    {
        clock_t timediff = m_CurrTime - m_StartTime;
        float ftime = ConvertClockTimeToFloat(timediff);
        
        return ftime;
    }
    
    clock_t currtime = GetStopWatchTime();
    clock_t timediff = currtime - m_StartTime;
    float ftime = ConvertClockTimeToFloat(timediff);
    
    return ftime;
}
/////////////////////////////////////////////////////////////////////////////////////////////
unsigned int CStopWatch::GetTicks()
{
    if(m_Paused)
    {
        clock_t timediff = m_CurrTime - m_StartTime;
        unsigned int uitime = ConvertClockTimeToUInt(timediff);
        return uitime;
    }
    
    clock_t currtime = GetStopWatchTime();
    clock_t timediff = currtime - m_StartTime;
    unsigned int uitime = ConvertClockTimeToUInt(timediff);
  
    return uitime;
}
/////////////////////////////////////////////////////////////////////////////////////////////
#endif






#if defined WINTIME_MEASURE
/////////////////////////////////////////////////////////////////////////////////////////////
inline unsigned int GetMicroSecTime()
{
    LARGE_INTEGER mstime;
    QueryPerformanceCounter(&mstime);
    return mstime;
}

/////////////////////////////////////////////////////////////////////////////////////////////
inline float ConvertMicroSecsToFloat(LARGE_INTEGER time_val)
{
    return float(time_val) / 1000000.f;
}
/////////////////////////////////////////////////////////////////////////////////////////////
inline unsigned int ConvertMicroSecsToUInt(LARGE_INTEGER time_val)
{
    return (unsigned int) time_val;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Stop watch time measure class
CHighResStopWatch::CHighResStopWatch(bool bactivate):
m_StartTime(0),
m_CurrTime(0),
m_Paused(true)
{
    QueryPerformanceFrequency((LARGE_INTEGER*)&m_HighResFreq);
    
    Reset();
    if(bactivate) Start();
}
/////////////////////////////////////////////////////////////////////////////////////////////
CHighResStopWatch::~CHighResStopWatch()
{
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CHighResStopWatch::Start()
{
    if(!IsPaused()) return ;

    m_Paused = false;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CHighResStopWatch::Stop()
{
    if(IsPaused()) return ;

    m_CurrTime = GetMicroSecTime();
    m_Paused = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CHighResStopWatch::Reset()
{
    m_StartTime = GetMicroSecTime();
    m_CurrTime = m_StartTime;
}
/////////////////////////////////////////////////////////////////////////////////////////////
bool CHighResStopWatch::IsPaused() const
{
    return m_Paused;
}

/////////////////////////////////////////////////////////////////////////////////////////////
float CHighResStopWatch::GetTime()
{
    if(m_Paused)
    {        
        LARGE_INTEGER timediff = m_CurrTime - m_StartTime;
        float ftime = (float)(double)timediff/(double)m_HighResFreq*1000000.0;
        
        return ftime;
    }
    
    LARGE_INTEGER currtime = GetMicroSecTime();
    LARGE_INTEGER timediff = currtime - m_StartTime;
    float ftime = (float)(double)timediff/(double)m_HighResFreq*1000000.0;
    
    return ftime;
}
/////////////////////////////////////////////////////////////////////////////////////////////
unsigned int CHighResStopWatch::GetTicks()
{
    if(m_Paused)
    {
        LARGE_INTEGER timediff = m_CurrTime - m_StartTime;
        float ftime = (float)(double)timediff/(double)m_HighResFreq*1000000.0;
        unsigned int uitime = (unsigned int) ftime;
        
        return uitime;
    }
    
    LARGE_INTEGER currtime = GetMicroSecTime();
    LARGE_INTEGER timediff = currtime - m_StartTime;
    float ftime = (float)(double)timediff/(double)m_HighResFreq*1000000.0;
    unsigned int uitime = (unsigned int) ftime;
  
    return uitime;
}

/////////////////////////////////////////////////////////////////////////////////////////////
#elif defined STDCHRONOLIB_TIME_MEASURE
/////////////////////////////////////////////////////////////////////////////////////////////

inline std::chrono::high_resolution_clock::time_point GetMicroSecTime()
{
    return std::chrono::high_resolution_clock::now();
}


/////////////////////////////////////////////////////////////////////////////////////////////
// Stop watch time measure class
CHighResStopWatch::CHighResStopWatch(bool bactivate):
m_Paused(true)
{
    Reset();
    if(bactivate) Start();
}
/////////////////////////////////////////////////////////////////////////////////////////////
CHighResStopWatch::~CHighResStopWatch()
{

}
/////////////////////////////////////////////////////////////////////////////////////////////
void CHighResStopWatch::Start()
{
    if(!IsPaused()) return ;

    m_Paused = false;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CHighResStopWatch::Stop()
{
    if(IsPaused()) return ;

    m_CurrTime = GetMicroSecTime();
    m_Paused = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CHighResStopWatch::Reset()
{
    m_StartTime = GetMicroSecTime();
    m_CurrTime = m_StartTime;
}
/////////////////////////////////////////////////////////////////////////////////////////////
bool CHighResStopWatch::IsPaused() const
{
    return m_Paused;
}

/////////////////////////////////////////////////////////////////////////////////////////////
float CHighResStopWatch::GetTime()
{
    if(m_Paused)
    {
        std::chrono::duration<float> fsec = m_CurrTime - m_StartTime;
        std::chrono::microseconds dsec = std::chrono::duration_cast<std::chrono::microseconds>(fsec);
        
        return (float)dsec.count() / 1000000.f;
    }
    
    std::chrono::high_resolution_clock::time_point currtime = GetMicroSecTime();
    std::chrono::duration<float> fsec = currtime - m_StartTime;
    std::chrono::microseconds dsec = std::chrono::duration_cast<std::chrono::microseconds>(fsec);
    
    return fsec.count() / 1000000.f;
}
/////////////////////////////////////////////////////////////////////////////////////////////
unsigned int CHighResStopWatch::GetTicks()
{
    if(m_Paused)
    {
        std::chrono::duration<float> fsec = m_CurrTime - m_StartTime;
        std::chrono::microseconds dsec = std::chrono::duration_cast<std::chrono::microseconds>(fsec);
        
        return (unsigned int)dsec.count();
    }
    
    std::chrono::high_resolution_clock::time_point currtime = GetMicroSecTime();
    std::chrono::duration<float> fsec = currtime - m_StartTime;
    std::chrono::microseconds dsec = std::chrono::duration_cast<std::chrono::microseconds>(fsec);
    
    return (unsigned int) fsec.count();
}
/////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////
#else // Use C time library
/////////////////////////////////////////////////////////////////////////////////////////////
inline clock_t GetMicroSecTime()
{
    return clock();
}

/////////////////////////////////////////////////////////////////////////////////////////////
inline float ConvertMicroSecsToFloat(clock_t time_val)
{
    return (float) time_val / CLOCKS_PER_SEC;
}
/////////////////////////////////////////////////////////////////////////////////////////////
inline unsigned int ConvertMicroSecsToUInt(clock_t time_val)
{
    return (unsigned int) time_val;
}
/////////////////////////////////////////////////////////////////////////////////////////////
CHighResStopWatch::CHighResStopWatch(bool bactivate):
m_StartTime(0),
m_CurrTime(0),
m_Paused(true)
{
    Reset();
    if(bactivate) Start();
}
/////////////////////////////////////////////////////////////////////////////////////////////
CHighResStopWatch::~CHighResStopWatch()
{
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CHighResStopWatch::Start()
{
    if(!IsPaused()) return ;

    m_Paused = false;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CHighResStopWatch::Stop()
{
    if(IsPaused()) return ;

    m_CurrTime = GetMicroSecTime();
    m_Paused = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CHighResStopWatch::Reset()
{
    m_StartTime = GetMicroSecTime();
    m_CurrTime = m_StartTime;
}
/////////////////////////////////////////////////////////////////////////////////////////////
bool CHighResStopWatch::IsPaused() const
{
    return m_Paused;
}

/////////////////////////////////////////////////////////////////////////////////////////////
float CHighResStopWatch::GetTime()
{
    if(m_Paused)
    {
        clock_t timediff = m_CurrTime - m_StartTime;
        float ftime = ConvertMicroSecsToFloat(timediff);
        
        return ftime;
    }
    
    clock_t currtime = GetMicroSecTime();
    clock_t timediff = currtime - m_StartTime;
    float ftime = ConvertMicroSecsToFloat(timediff);
    
    return ftime;
}
/////////////////////////////////////////////////////////////////////////////////////////////
unsigned int CHighResStopWatch::GetTicks()
{
    if(m_Paused)
    {
        clock_t timediff = m_CurrTime - m_StartTime;
        unsigned int uitime = ConvertMicroSecsToUInt(timediff);
        return uitime;
    }
    
    clock_t currtime = GetMicroSecTime();
    clock_t timediff = currtime - m_StartTime;
    unsigned int uitime = ConvertMicroSecsToUInt(timediff);
  
    return uitime;
}
#endif

