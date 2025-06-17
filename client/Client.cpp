#include "Client.hpp"

std::string& Client::getBuffer(void){
    return (this->Buffer);
}

std::vector<std::string>& Client::getCmds(void){
    return (cmds);
}

void Client::AddBuffer(const char *buf){
    this->Buffer += buf;
}

void Client::extract_cmds(void){
    size_t pos = 0;
    
    while ((pos = Buffer.find("\r\n")) != std::string::npos) {
        std::string command = Buffer.substr(0, pos);
        
        if (!command.empty()) {
            cmds.push_back(command);
        }
        Buffer.erase(0, pos + 2);
    }
}
