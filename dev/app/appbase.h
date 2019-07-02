///////////////////////////////////////////////////////////////////////////////////////
// appbase.cpp
//
// Application base class declaration
///////////////////////////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_BASE_H__
#define __APPLICATION_BASE_H__

#include <stdio.h>
#include <vector>
#include <string>
#include "evtlistener.h"

using namespace std;

class CWindowSystem;


///////////////////////////////////////////////////////////////////////////////////////
class CApplicationBase //: public InputEventListener
{
private:
    //CApplicationBase() = delete;
    //CApplicationBase(const CApplicationBase&) = delete;
    //CApplicationBase operator = (const CApplicationBase&) = delete;

protected:
    CApplicationBase(const string &app_name, const vector<string> &args, InputEventListener *listener);
    CApplicationBase(string &&app_name, vector<string> &&args, InputEventListener *listener);
    
public:
    virtual ~CApplicationBase();
    
    virtual void Init() = 0;
    virtual void Release() = 0;
    
    void Run();
    int Result();
    
    string GetAppName() const;
    
protected:
    void SetInitSuccess();
    void SetReleaseSuccess();
    
    bool IsInitSucceded() const;
    bool IsReleaseSucceded() const;
    
    bool IsAppRunning() const;
    void StopApp();
    
    size_t GetArgsCount() const;
    string GetArgs(size_t index) const;
    
    virtual void RunMainProcess();
    
    
    
protected:
    bool CreateDisplayWindow();
    
    
private:
    vector<string> mArgs;
    string mAppName;
    
    bool mAppInited;
    bool mAppReleased;
    
    bool mAppRunning;
    
    InputEventListener *mListener;
    CWindowSystem *mWinSys;
};
///////////////////////////////////////////////////////////////////////////////////////

#endif // __APPLICATION_BASE_H__
///////////////////////////////////////////////////////////////////////////////////////
