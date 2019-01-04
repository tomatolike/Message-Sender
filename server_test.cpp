#include <iostream>
#include <string>
#include "server_api.h"

int main(){
    
    if(!ServerApi::Connect("193.112.104.61:2182")){
        std::cout << "Connect Failed" << std::endl;
        return 0;
    }

    if(!ServerApi::CreateRoot("/abc")){
        std::cout << "Create Root Failed" << std::endl;
        return 0;
    }

    while(true){
        std::string temp;
        std::cin >> temp;
        if(temp.compare("END") == 0)break;
        if(!ServerApi::ChangeMessage(temp)){
            std::cout << "Message Change Failed" << std::endl;
        }
    }

    ServerApi::Close();
    std::cout << "session close" << std::endl;
    return 0;
}