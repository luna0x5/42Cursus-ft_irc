#include "Channel.hpp"

Channel::Channel():Name(""), Password("hello"), paswrd(1){

}

Channel::~Channel(){

}

// Channel::Channel(std::string name):Name(name){

// }

std::string& Channel::GetName(void){return Name;}

void Channel::SetName(std::string& name){Name=name;}

std::string& Channel::GetPassword(void){
    return Password;
}

void Channel::SetPassword(std::string& password){
    Password = password;
}

std::vector<Client>& Channel::GetMembers(void){
return members;
}

std::vector<Client>& Channel::GetOps(void){
    return Ops;
}

bool Channel::GetBoolPswd(void){
    return paswrd;
}

void Channel::SitBoolPswd(bool is){
    paswrd = is;
}