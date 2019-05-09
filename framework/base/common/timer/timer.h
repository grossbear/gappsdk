/////////////////////////////////////////////////////////////////////////////////////////////
// timer.h
//
// Time Measure Stop Watch Classes
////////////////////////////////////////////////////////////////////////////////////////////

#ifdef WINTIME_MEASURE
#define MILLISEC_TIME unsigned int
#else
#include <time.h>
#define MILLISEC_TIME clock_t
#endif // time measure variables

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

    float GetTime();
    unsigned int GetTicks();

protected:
    MILLISEC_TIME mStartTime;
    MILLISEC_TIME mCurrTime;

    bool mActive;
};

/////////////////////////////////////////////////////////////////////////////////////////////
class CHighResStopWatch
{
public:
    CHighResStopWatch();
    ~CHighResStopWatch();

protected:
};

/////////////////////////////////////////////////////////////////////////////////////////////
class CNanoStopWatch
{
public:
    CNanoStopWatch();
    ~CNanoStopWatch();

protected:
};

/////////////////////////////////////////////////////////////////////////////////////////////