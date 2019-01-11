/////////////////////////////////////////////////////////////////////////////////////////////
// stopwatch.h
//
// Time measure stop watch classes declarations
////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __STOPWATCH_H__
#define __STOPWATCH_H__


//CLIBTIME_MEASURE
//#define STDCHRONOLIB_TIME_MEASURE
//#define WINTIME_MEASURE

#if defined STDCHRONOLIB_TIME_MEASURE

#include <chrono>
#define MILLISECS_TIME std::chrono::steady_clock::time_point
#define MICROSECS_TIME std::chrono::high_resolution_clock::time_point
#define NANOSECS_TIME  std::chrono::high_resolution_clock::time_point

#elif defined WINTIME_MEASURE

#include <windows.h>
#include <MMSystem.h>
#define MILLISECS_TIME DWORD
#define MICROSECS_TIME __int64

#else

#include <time.h>
#define MILLISECS_TIME clock_t
#define MICROSECS_TIME clock_t

#endif // time measure variables

/////////////////////////////////////////////////////////////////////////////////////////////
// Low res stopwatch that gives time in milliseconds
class CStopWatch
{
public:
    CStopWatch(bool bactivate=true);
    ~CStopWatch();
    
    void Start();
    void Stop();
    void Reset();
    
    bool IsPaused() const;
    
    float GetTime();
    unsigned int GetTicks();
    
protected:
    MILLISECS_TIME m_StartTime;
    MILLISECS_TIME m_CurrTime;
    
    bool m_Paused;
};
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
// Stopwatch high res time measure class
class CHighResStopWatch
{
public:
    CHighResStopWatch(bool bactivate=true);
    ~CHighResStopWatch();

    void Start();
    void Stop();
    void Reset();

    bool IsPaused() const;

    float GetTime();
    unsigned int GetTicks();
    
protected:
    MICROSECS_TIME m_StartTime;
    MICROSECS_TIME m_CurrTime;
#ifdef WINTIME_MEASURE
    MICROSECS_TIME m_HighResFreq;
#endif //WINTIME_MEASURE

    bool m_Paused;
};
/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef STDCHRONOLIB_TIME_MEASURE
/////////////////////////////////////////////////////////////////////////////////////////////
// Stopwatch nanoseconds time measure class
class CNanoStopWatch
{
public:
    CNanoStopWatch(bool bactivate=true);
    ~CNanoStopWatch();
    
    void Start();
    void Stop();
    void Reset();
    
    bool IsPaused() const;
    
    double GetTime();
    unsigned int GetTicks();
    
protected:
    NANOSECS_TIME m_StartTime;
    NANOSECS_TIME m_CurrTime;
    
    bool m_Paused;
};

#endif //STDCHRONOLIB_TIME_MEASURE

#endif //__STOPWATCH_H__
