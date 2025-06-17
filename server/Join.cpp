#include "Server.hpp"

void Server::JOIN(void){
    if (line.size()<=1 || line.size()>=3){
        std::cerr<<"Error join"<<std::endl;
        return;
    }
}
