///////////////////////////////////////////////////////////////////////////////////////
// appbase.h
//
// Application base class declaration
///////////////////////////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_BASE_H__
#define __APPLICATION_BASE_H__

#include <vector>
#include <string>

class CApplicationBase
{
public:
     CApplicationBase() = delete;
     CApplicationBase(const CApplicationBase&) = delete;
     CApplicationBase & operator = (const CApplicationBase&) = delete;
     CApplicationBase(const std::string &app_name, const std::vector<std::string> &args);

     CApplicationBase(std::string &&app_name, std::vector<std::string> &&args);

     virtual ~CApplicationBase();

     virtual bool Init();
     virtual bool Run();
     virtual bool Release();

protected:
     virtual bool RunMainProcess();

     std::string GetAppName() const;
     int GetArgsCount() const;
     std::string GetArg(int index) const;

private:
     const std::string mAppName;
     const std::vector<std::string> mArgs;
};

#endif //__APPLICATION_BASE_H__
