///////////////////////////////////////////////////////////////////////////////////////
// main.cpp
//
// Program main function
///////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <utility>
#include "appbase.h"

extern CApplicationBase* CreateApplication(vector<string> &&args);

///////////////////////////////////////////////////////////////////////////////////////
// Copy input arguments into arguments vector
vector<string> get_args_vec(int argc, char *argv[])
{
    vector<string> args_vec;
    for(int i = 1; i < argc; i++)
    {
        string str_arg(argv[i]);
      args_vec.push_back(std::move(str_arg));     
    }
    return std::move(args_vec);
}

int del_app_get_result(CApplicationBase *app)
{
    int result = app->Result();
    delete (app);
    
    return result;
}

// Programm entry point
int main(int argc, char *argv[])
{
    printf("App research prog\n");
    vector<string> args = get_args_vec(argc,argv);
    
    CApplicationBase *app = CreateApplication(std::move(args));
    
    app->Init();
    app->Run();
    app->Release();
    
    return del_app_get_result(app);
}