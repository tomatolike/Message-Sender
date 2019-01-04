#include <iostream>
#include <string>
#include "client_api.h"

int version = 0;
std::string message = "";

void show_message(std::string message)
{
    std::cout << message << std::endl;
}

int main(){
    
    if(!ClientApi::Connect("193.112.104.61:2182")){
        std::cout << "Connect Failed" << std::endl;
        return 0;
    }

    if(!ClientApi::ListenRoot("/abc",show_message)){
        std::cout << "Listen Root Failed" << std::endl;
        return 0;
    }

    version = ClientApi::GetVersion();

    while(true){
        /*if(!ClientApi::VersionCheck(version)){
            message = ClientApi::GetMessage();
            std::cout << message << std::endl;
        }*/
        std::string temp;
        std::cin >> temp;
        if(temp.compare("END") == 0)break;
    }

    ClientApi::Close();
    std::cout << "session close" << std::endl;
    return 0;
}