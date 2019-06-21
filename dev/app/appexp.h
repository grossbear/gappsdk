///////////////////////////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_EXPERIMENTAL_H__
#define __APPLICATION_EXPERIMENTAL_H__

#include "appbase.h"

///////////////////////////////////////////////////////////////////////////////////////
class CAppExp : public CApplicationBase
{
public:
    CAppExp(const vector<string> &args);
    CAppExp(vector<string> &&args);
    ~CAppExp();
    
    virtual void Init() override;
    virtual void Release() override;
    
    virtual void OnQuit() override;
    virtual void OnClose() override;
    
protected:
    virtual void RunMainProcess() override;
};
///////////////////////////////////////////////////////////////////////////////////////

#endif //__APPLICATION_EXPERIMENTAL_H__