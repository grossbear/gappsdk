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
    
    virtual void OnQuit();
    virtual void OnClose();
    
protected:
    virtual void RunMainProcess() override;
    
    class ExpAppEventListener : public InputEventListener {
    public:
        ExpAppEventListener(CAppExp *app):mApp(app){}
        ~ExpAppEventListener(){mApp=nullptr;}
        
        virtual void OnQuitEvt(){mApp->OnQuit();}
        virtual void OnCloseEvt(){mApp->OnClose();}
    private:
        CAppExp *mApp;
    };

};
///////////////////////////////////////////////////////////////////////////////////////

#endif //__APPLICATION_EXPERIMENTAL_H__