///////////////////////////////////////////////////////////////////////////////////////
// evtlistener.h
//
// Event listener interface
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
class EventListener
{
public:
    EventListener(){}
    virtual ~EventListener(){}
    
    virtual void OnKeyDown(unsigned key){}
    virtual void OnKeyUp(unsigned key){}
    
    virtual void OnMouseBtnDown(int x, int y){}
    virtual void OnMouseBtnUp(int x, int y){}
    
    virtual void OnSetSize(int w, int h){}
    
    virtual void OnQuit(){}
    virtual void OnClose(){}
};
///////////////////////////////////////////////////////////////////////////////////////