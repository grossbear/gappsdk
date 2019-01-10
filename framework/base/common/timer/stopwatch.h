/////////////////////////////////////////////////////////////////////////////////////////////
// stopwatch.h
//
// Time measure stop watch classes declarations
////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __STOPWATCH_H__
#define __STOPWATCH_H__

//#define WINTIME_MEASURE
//#define CLIBTIME_MEASURE
#define STDCHRONOLIB_TIME_MEASURE

#if defined WINTIME_MEASURE
#include <windows.h>
#endif //WINTIME_MEASURE

#if defined STDCHRONOLIB_TIME_MEASURE
#include <chrono>
#endif //STDCHRONOLIB_TIME_MEASURE

/*
#if defined WINTIME_MEASURE
//#include <windows.h>
//#include <MMSystem.h>

#define CLOCK_TIME unsigned int
#define MICROSEC_TIME __int64

#elif defined CHRONOLIB_TIME_MEASURE
#include <chrono>
#define CLOCK_TIME std::chrono::steady_clock::time_point
#define MICROSEC_TIME std::chrono::steady_clock::time_point
//#define CLOCK_TIME std::chrono::milliseconds;
//#define MICROSEC_TIME std::chrono::microseconds;

#else
#include <time.h>
#define CLOCK_TIME clock_t
#define MICROSEC_TIME clock_t

#endif // time measure variables
*/

// Low Res timer
#if defined WINTIME_MEASURE
/////////////////////////////////////////////////////////////////////////////////////////////
class CStopWatch
{
public:
    CStopWatch(bool activate=true);
    ~CStopWatch();

    void Start();
    void Stop();
    void Reset();

    bool IsPaused() const;

    float GetTime();
    unsigned int GetTicks();

protected:
    DWORD m_StartTime;
    DWORD m_CurrTime;

    bool m_Paused;
};
/////////////////////////////////////////////////////////////////////////////////////////////
#elif defined STDCHRONOLIB_TIME_MEASURE
/////////////////////////////////////////////////////////////////////////////////////////////
class CStopWatch
{
public:
    CStopWatch(bool activate=true);
    ~CStopWatch();

    void Start();
    void Stop();
    void Reset();

    bool IsPaused() const;

    float GetTime();
    unsigned int GetTicks();

protected:
    std::chrono::steady_clock::time_point m_StartTime;
    std::chrono::steady_clock::time_point m_CurrTime;

    bool m_Paused;
};
/////////////////////////////////////////////////////////////////////////////////////////////
#else // Use C time library
/////////////////////////////////////////////////////////////////////////////////////////////

#include <time.h>

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
    clock_t m_StartTime;
    clock_t m_CurrTime;

    bool m_Paused;
};
/////////////////////////////////////////////////////////////////////////////////////////////
#endif //

/////////////////////////////////////////////////////////////////////////////////////////////
#if defined WINTIME_MEASURE
class CHighResStopWatch
{
public:
    CHighResStopWatch(bool bstart=true);
    ~CHighResStopWatch();

    void Start();
    void Stop();
    void Reset();

    bool IsPaused() const;

    float GetTime();
    unsigned int GetTicks();

protected:
    LARGE_INTEGER m_StartTime;
    LARGE_INTEGER m_CurrTime;
    LARGE_INTEGER m_HighResFreq;

    bool m_Paused;
};
/////////////////////////////////////////////////////////////////////////////////////////////
#elif defined STDCHRONOLIB_TIME_MEASURE
class CHighResStopWatch
{
public:
    CHighResStopWatch(bool activate=true);
    ~CHighResStopWatch();

    void Start();
    void Stop();
    void Reset();

    bool IsPaused() const;

    float GetTime();
    unsigned int GetTicks();

protected:
    std::chrono::high_resolution_clock::time_point m_StartTime;
    std::chrono::high_resolution_clock::time_point m_CurrTime;

    bool m_Paused;
};
/////////////////////////////////////////////////////////////////////////////////////////////
#else // Use C time library
class CHighResStopWatch
{
public:
    CHighResStopWatch(bool bstart=true);
    ~CHighResStopWatch();

    void Start();
    void Stop();
    void Reset();

    bool IsPaused() const;

    float GetTime();
    unsigned int GetTicks();

protected:
    clock_t m_StartTime;
    clock_t m_CurrTime;

    bool m_Paused;
};
#endif
/////////////////////////////////////////////////////////////////////////////////////////////

/*
/////////////////////////////////////////////////////////////////////////////////////////////
class CStopWatch
{
public:
    CStopWatch(bool bstart=true);
    ~CStopWatch();

    void Start();
    void Stop();
    void Reset();

    bool IsActive() const;
    bool IsHighRes() const;

    float GetTime();
    unsigned int GetTicks();

protected:
    CLOCK_TIME m_StartTime;
    CLOCK_TIME m_CurrTime;

    bool m_Active;
};

/////////////////////////////////////////////////////////////////////////////////////////////
class CHighResStopWatch
{
public:
    CHighResStopWatch(bool bstart=true);
    ~CHighResStopWatch();

    void Start();
    void Stop();
    void Reset();

    bool IsActive() const;

    float GetTime();
    unsigned int GetTicks();

protected:
    MICROSEC_TIME m_StartTime;
    MICROSEC_TIME m_CurrTime;
#ifdef WINTIME_MEASURE
    MICROSEC_TIME m_HighResFreq;
#endif //WINTIME_MEASURE
    bool m_Active;
};

/////////////////////////////////////////////////////////////////////////////////////////////
class CNanoStopWatch
{
public:
    CNanoStopWatch();
    ~CNanoStopWatch();

protected:
};
*/
/////////////////////////////////////////////////////////////////////////////////////////////

#endif //__STOPWATCH_H__
