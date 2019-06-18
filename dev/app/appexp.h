///////////////////////////////////////////////////////////////////////////////////////
#include "appbase.h"

class CAppExp : public CApplicationBase
{
public:
    CAppExp(const vector<string> &args);
    CAppExp(vector<string> &&args);
    ~CAppExp();
    
    virtual void Init() override;
    virtual void Release() override;
    
    
protected:
};
///////////////////////////////////////////////////////////////////////////////////////