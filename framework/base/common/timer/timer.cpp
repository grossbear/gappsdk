/////////////////////////////////////////////////////////////////////////////////////////////
// timer.cpp
//
// Time Measure Stop Watch Classes
/////////////////////////////////////////////////////////////////////////////////////////////

#include "timer.h"

/////////////////////////////////////////////////////////////////////////////////////////////
//Get time function
inline MILLISEC_TIME GetStopWatchTime()
{
#ifdef WINTIME_MEASURE
    return timeGetTime();
#else
    return clock();
#endif //time measure variables
}

/////////////////////////////////////////////////////////////////////////////////////////////
//Time value convertion function
inline float ConvertMilliSecsToFloat(MILLISEC_TIME time_val)
{
#ifdef WINTIME_MEASURE
    return float(time_val) / 1000.0f;
#else
    return (float) time_val/CLOCKS_PER_SEC;
#endif //time measure variables
}
/////////////////////////////////////////////////////////////////////////////////////////////
inline unsigned int ConvertMilliSecsToUInt(MILLISEC_TIME time_val)
{
#ifdef WINTIME_MEASURE
    return (unsigned int) time_val;
#else
    return (unsigned int) time_val;
#endif //time measure variables
}

/////////////////////////////////////////////////////////////////////////////////////////////
CStopWatch::CStopWatch(bool bstart):mStartTime(0),mCurrTime(0),mActive(false)
{
    Reset();
    if(bstart) Start();
}
/////////////////////////////////////////////////////////////////////////////////////////////
CStopWatch::~CStopWatch()
{
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CStopWatch::Start()
{
    if(IsActive()) return ;

    mActive = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CStopWatch::Stop()
{
    if(!IsActive()) return ;

    mCurrTime = GetStopWatchTime();
    mActive = false;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CStopWatch::Reset()
{
    mStartTime = GetStopWatchTime();
    mCurrTime = mStartTime;
}
/////////////////////////////////////////////////////////////////////////////////////////////
bool CStopWatch::IsActive() const
{
    return mActive;
}
/////////////////////////////////////////////////////////////////////////////////////////////
float CStopWatch::GetTime()
{
    if(!IsActive())
    {
        return ConvertMilliSecsToFloat(mCurrTime - mStartTime);
    }

    return ConvertMilliSecsToFloat(GetStopWatchTime() - mStartTime);
}
/////////////////////////////////////////////////////////////////////////////////////////////
unsigned int CStopWatch::GetTicks()
{
    if(!IsActive())
    {
        return ConvertMilliSecsToUInt(mCurrTime - mStartTime);
    }

    return ConvertMilliSecsToUInt(GetStopWatchTime() - mStartTime);
}
/////////////////////////////////////////////////////////////////////////////////////////////

