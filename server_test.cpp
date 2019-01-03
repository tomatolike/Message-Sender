#include <iostream>
#include <string>
#include "Server_API/Server_API.h"

int main(){
    
    if(!Server_API::Connect("193.112.104.61:2182")){
        std::cout << "Connect Failed" << std::endl;
        return 0;
    }

    if(!Server_API::Create_root("/abc")){
        std::cout << "Create Root Failed" << std::endl;
        return 0;
    }

    while(true){
        std::string temp;
        std::cin >> temp;
        if(temp.compare("END") == 0)break;
        if(!Server_API::Change_message(temp)){
            std::cout << "Message Change Failed" << std::endl;
        }
    }

    Server_API::Close();
    std::cout << "session close" << std::endl;
    return 0;
}