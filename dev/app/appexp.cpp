///////////////////////////////////////////////////////////////////////////////////////
#include "appexp.h"
///////////////////////////////////////////////////////////////////////////////////////
#define APPEXP_NAME "AppExp"

CApplicationBase* CreateApplication(vector<string> &&args)
{
    return new CAppExp(std::move(args));
}

CAppExp::CAppExp(const vector<string> &args):CApplicationBase(APPEXP_NAME,args)
{
    printf("CAppExp constructor l-value\n");
}

CAppExp::CAppExp(vector<string> &&args):CApplicationBase(APPEXP_NAME,std::move(args))
{
    printf("CAppExp constructor r-value\n");
}

CAppExp::~CAppExp()
{
    printf("CAppExp destructor\n");
}

void CAppExp::Init()
{
    printf("App experiment Init func\n");
    SetInitSuccess();
}

void CAppExp::Release()
{
    printf("App experiment Release func\n");
    SetReleaseSuccess();
}
///////////////////////////////////////////////////////////////////////////////////////