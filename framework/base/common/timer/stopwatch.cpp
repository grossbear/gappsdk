/////////////////////////////////////////////////////////////////////////////////////////////
// stopwatch.cpp
//
// Time measure stop watch classes defintions
//
// Warning: classes do not handle unsigned integers overflow. Ex. if in windows timer passed
// In Windows after 49 days time function will be reseted and starts counting from beginning.
// Nano stopwatch should be used for receiving small tick counts.
// MinGW compiler on Windows C language time library has precision in milliseconds and
// on Linux gcc compiler same library returns time in microseconds.
// 
// Remark: Think about merging all three classes into single template class.
/////////////////////////////////////////////////////////////////////////////////////////////

#include "stopwatch.h"

/////////////////////////////////////////////////////////////////////////////////////////////
// Stopwatch time measure class
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
inline MILLISECS_TIME GetMilliSecsTime()
{
#if defined STDCHRONOLIB_TIME_MEASURE
    return std::chrono::steady_clock::now();
#elif defined WINTIME_MEASURE
    return timeGetTime();
#else
    return clock();
#endif
}
/////////////////////////////////////////////////////////////////////////////////////////////
inline float CalcMilliSecsTimeInFloat(MILLISECS_TIME curr_time, MILLISECS_TIME prev_time)
{
#if defined STDCHRONOLIB_TIME_MEASURE
    std::chrono::duration<float> timespan = curr_time - prev_time;
    std::chrono::milliseconds millisecs = std::chrono::duration_cast<std::chrono::milliseconds>(timespan);
    return (float)millisecs.count() / 1000.f;
#elif defined WINTIME_MEASURE
    MILLISECS_TIME timespan = curr_time - prev_time;
    return float(timespan) / 1000.0f;
#else
    MILLISECS_TIME timespan = curr_time - prev_time;
    return (float) timespan / CLOCKS_PER_SEC;
#endif
}
/////////////////////////////////////////////////////////////////////////////////////////////
inline unsigned int CalcMilliSecsTimeInUInt(MILLISECS_TIME curr_time, MILLISECS_TIME prev_time)
{
#if defined STDCHRONOLIB_TIME_MEASURE
    std::chrono::duration<float> timespan = curr_time - prev_time;
    std::chrono::milliseconds millisecs = std::chrono::duration_cast<std::chrono::milliseconds>(timespan);
    return (unsigned int) millisecs.count();
#elif defined WINTIME_MEASURE
    MILLISECS_TIME timespan = curr_time - prev_time;
    return (unsigned int) timespan;
#else
    MILLISECS_TIME timespan = curr_time - prev_time;
    return ((unsigned int) timespan) / 1000;
#endif    
}
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
CStopWatch::CStopWatch(bool bactivate):
m_Paused(true)
{
#ifdef WINTIME_MEASURE
    timeBeginPeriod(1);
#endif //WINTIME_MEASURE
    
    Reset();
    if(bactivate) Start();
}
/////////////////////////////////////////////////////////////////////////////////////////////
CStopWatch::~CStopWatch()
{
//#ifdef WINTIME_MEASURE
    //--timeEndPeriod(1);
//#endif //WINTIME_MEASURE
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

    m_CurrTime = GetMilliSecsTime();
    m_Paused = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CStopWatch::Reset()
{
    m_StartTime = GetMilliSecsTime();
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
        float ftime = CalcMilliSecsTimeInFloat(m_CurrTime, m_StartTime);
        return ftime;
    }
    
    MILLISECS_TIME currtime = GetMilliSecsTime();
    float ftime = CalcMilliSecsTimeInFloat(currtime, m_StartTime);
    return ftime;
}
/////////////////////////////////////////////////////////////////////////////////////////////
unsigned int CStopWatch::GetTicks()
{
    if(m_Paused)
    {
        unsigned int uitime = CalcMilliSecsTimeInUInt(m_CurrTime, m_StartTime);
        return uitime;
    }
    
    MILLISECS_TIME currtime = GetMilliSecsTime();
    unsigned int uitime = CalcMilliSecsTimeInUInt(currtime, m_StartTime);
    return uitime;
}
/////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////
// Stopwatch high res time measure class
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
inline MICROSECS_TIME GetMicroSecsTime()
{
#if defined STDCHRONOLIB_TIME_MEASURE
    return std::chrono::high_resolution_clock::now();
#elif defined WINTIME_MEASURE
    MICROSECS_TIME mstime;
    QueryPerformanceCounter((LARGE_INTEGER*)&mstime);
    return mstime;
#else
    return clock();
#endif
}
/////////////////////////////////////////////////////////////////////////////////////////////
inline float CalcMicroSecsTimeInFloat(MICROSECS_TIME curr_time, MICROSECS_TIME prev_time)
{
#if defined STDCHRONOLIB_TIME_MEASURE
    std::chrono::duration<float> timespan = curr_time - prev_time;
    std::chrono::microseconds microsecs = std::chrono::duration_cast<std::chrono::microseconds>(timespan);
    return (float)microsecs.count() / 1000000.f;
#elif defined WINTIME_MEASURE
    MICROSECS_TIME timespan = curr_time - prev_time;
    return (float)(double)timespan/(double)m_HighResFreq;
#else
    MICROSECS_TIME timespan = curr_time - prev_time;
    return (float) timespan / CLOCKS_PER_SEC;
#endif
}
/////////////////////////////////////////////////////////////////////////////////////////////
inline unsigned int CalcMicroSecsTimeInUInt(MICROSECS_TIME curr_time, MICROSECS_TIME prev_time)
{
#if defined STDCHRONOLIB_TIME_MEASURE
    std::chrono::duration<float> timespan = curr_time - prev_time;
    std::chrono::microseconds microsecs = std::chrono::duration_cast<std::chrono::microseconds>(timespan);
    return (unsigned int) microsecs.count();
#elif defined WINTIME_MEASURE
    MICROSECS_TIME timespan = curr_time - prev_time;
    return (float)(double)timespan/(double)m_HighResFreq*1000000.0;
#else
    MILLISECS_TIME timespan = curr_time - prev_time;
    return (unsigned int) timespan;
#endif    
}
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
CHighResStopWatch::CHighResStopWatch(bool bactivate):
m_Paused(true)
{
#ifdef WINTIME_MEASURE
    QueryPerformanceFrequency((LARGE_INTEGER*)&m_HighResFreq);
#endif //WINTIME_MEASURE

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

    m_CurrTime = GetMicroSecsTime();
    m_Paused = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CHighResStopWatch::Reset()
{
    m_StartTime = GetMicroSecsTime();
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
        float ftime = CalcMicroSecsTimeInFloat(m_CurrTime, m_StartTime);     
        return ftime;
    }
    
    MICROSECS_TIME currtime = GetMicroSecsTime();
    float ftime = CalcMicroSecsTimeInFloat(currtime, m_StartTime);
    return ftime;
}
/////////////////////////////////////////////////////////////////////////////////////////////
unsigned int CHighResStopWatch::GetTicks()
{
    if(m_Paused)
    {        
        unsigned int uitime = CalcMicroSecsTimeInUInt(m_CurrTime, m_StartTime);
        return uitime;
    }
    
    MICROSECS_TIME currtime = GetMicroSecsTime();
    unsigned int uitime = CalcMicroSecsTimeInUInt(currtime, m_StartTime);
    return uitime;
}
/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef STDCHRONOLIB_TIME_MEASURE
/////////////////////////////////////////////////////////////////////////////////////////////
// Stopwatch nanoseconds time measure class
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
inline NANOSECS_TIME GetNanoSecsTime()
{
    return std::chrono::high_resolution_clock::now();
}
/////////////////////////////////////////////////////////////////////////////////////////////
inline double CalcNanoSecsTimeInDouble(NANOSECS_TIME curr_time, NANOSECS_TIME prev_time)
{
    std::chrono::duration<double> timespan = curr_time - prev_time;
    std::chrono::nanoseconds nanosecs = std::chrono::duration_cast<std::chrono::nanoseconds>(timespan);
    return (double)nanosecs.count() / 1000000000.0;
}
/////////////////////////////////////////////////////////////////////////////////////////////
inline unsigned int CalcNanoSecsTimeInUInt(NANOSECS_TIME curr_time, NANOSECS_TIME prev_time)
{
    std::chrono::duration<double> timespan = curr_time - prev_time;
    std::chrono::nanoseconds nanosecs = std::chrono::duration_cast<std::chrono::nanoseconds>(timespan);
    return (unsigned int) nanosecs.count();
}
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
CNanoStopWatch::CNanoStopWatch(bool bactivate):
m_Paused(true)
{
    Reset();
    if(bactivate) Start();
}
/////////////////////////////////////////////////////////////////////////////////////////////
CNanoStopWatch::~CNanoStopWatch()
{
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CNanoStopWatch::Start()
{
    if(!IsPaused()) return ;

    m_Paused = false;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CNanoStopWatch::Stop()
{
    if(IsPaused()) return ;

    m_CurrTime = GetNanoSecsTime();
    m_Paused = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CNanoStopWatch::Reset()
{
    m_StartTime = GetNanoSecsTime();
    m_CurrTime = m_StartTime;
}
/////////////////////////////////////////////////////////////////////////////////////////////
bool CNanoStopWatch::IsPaused() const
{
    return m_Paused;
}

/////////////////////////////////////////////////////////////////////////////////////////////
double CNanoStopWatch::GetTime()
{
    if(m_Paused)
    {        
        double dbltime = CalcNanoSecsTimeInDouble(m_CurrTime, m_StartTime);     
        return dbltime;
    }
    
    NANOSECS_TIME currtime = GetNanoSecsTime();
    double dbltime = CalcNanoSecsTimeInDouble(currtime, m_StartTime);
    return dbltime;
}
/////////////////////////////////////////////////////////////////////////////////////////////
unsigned int CNanoStopWatch::GetTicks()
{
    if(m_Paused)
    {        
        unsigned int uitime = CalcNanoSecsTimeInUInt(m_CurrTime, m_StartTime);
        return uitime;
    }
    
    NANOSECS_TIME currtime = GetNanoSecsTime();
    unsigned int uitime = CalcNanoSecsTimeInUInt(currtime, m_StartTime);
    return uitime;
}
/////////////////////////////////////////////////////////////////////////////////////////////
#endif //STDCHRONOLIB_TIME_MEASURE