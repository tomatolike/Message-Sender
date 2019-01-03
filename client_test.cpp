#include <iostream>
#include <string>
#include "Client_API/Client_API.h"

int version = 0;
std::string message = "";

void show_message(std::string message)
{
    std::cout << message << std::endl;
}

int main(){
    
    if(!Client_API::Connect("193.112.104.61:2182")){
        std::cout << "Connect Failed" << std::endl;
        return 0;
    }

    if(!Client_API::Listen_root("/abc",show_message)){
        std::cout << "Listen Root Failed" << std::endl;
        return 0;
    }

    version = Client_API::Get_Version();

    while(true){
        /*if(!Client_API::Version_Check(version)){
            message = Client_API::Get_Message();
            std::cout << message << std::endl;
        }*/
        std::string temp;
        std::cin >> temp;
        if(temp.compare("END") == 0)break;
    }

    Client_API::Close();
    std::cout << "session close" << std::endl;
    return 0;
}