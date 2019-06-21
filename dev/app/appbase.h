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
class CApplicationBase : public EventListener
{
private:
    CApplicationBase() = delete;
    CApplicationBase(const CApplicationBase&) = delete;
    CApplicationBase operator = (const CApplicationBase&) = delete;

protected:
    CApplicationBase(const string &app_name, const vector<string> &args);
    CApplicationBase(string &&app_name, vector<string> &&args);
    
public:
    virtual ~CApplicationBase();
    
    virtual void Init();
    virtual void Release();
    
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
    
    virtual void RunMainProcess();
    
    bool CreateWindow();
    
protected:
    size_t GetArgsCount() const;
    string GetArgs(size_t index) const;
    
private:
    vector<string> mArgs;
    string mAppName;
    
    bool mAppInited;
    bool mAppReleased;
    
    bool mAppRunning;
    
    CWindowSystem *mWinSys;
};
///////////////////////////////////////////////////////////////////////////////////////

#endif // __APPLICATION_BASE_H__
///////////////////////////////////////////////////////////////////////////////////////