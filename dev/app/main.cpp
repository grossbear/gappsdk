#include <utility>
#include <iostream>
#include <vector>
#include <string>
#include "appbase.h"


// Copy input arguments into arguments vector
std::vector<std::string> get_args_vec(int argc, char *argv[])
{
    std::vector<std::string> args_vec;
    for(int i = 1; i < argc; i++)
    {
        std::string str_arg(argv[i]);
        args_vec.push_back(std::move(str_arg));
    }

    return std::move(args_vec);
}


// Programm entry point
int main(int argc, char *argv[])
{
    std::vector<std::string> argsvec = get_args_vec(argc,argv);

    for(auto &s: argsvec)
        std::cout << "string = " << s << std::endl;


    CApplicationBase *app = new CApplicationBase("appname",std::move(argsvec));
    app->Init();
    app->Run();
    app->Release();
    delete (app);

    return 0;
}
