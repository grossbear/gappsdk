///////////////////////////////////////////////////////////////////////////////////////
// evtlistener.h
//
// Event listener interface
///////////////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_LISTENER_H__
#define __EVENT_LISTENER_H__

///////////////////////////////////////////////////////////////////////////////////////
class InputEventListener
{
public:
    InputEventListener(){}
    virtual ~InputEventListener(){}
    
    virtual void OnKeyDownEvt(unsigned key){}
    virtual void OnKeyUpEvt(unsigned key){}
    
    virtual void OnMouseBtnDownEvt(int x, int y){}
    virtual void OnMouseBtnUpEvt(int x, int y){}
    
    virtual void OnWindowSetSizeEvt(int w, int h){}
    
    virtual void OnQuitEvt(){}
    virtual void OnCloseEvt(){}
};
///////////////////////////////////////////////////////////////////////////////////////

#endif //__EVENT_LISTENER_H__