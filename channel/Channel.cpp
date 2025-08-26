#include "Channel.hpp"

Channel::Channel():Name("default"), j_inviteOnly(false), _restrectedTopic(true), _keyed(true), _userLimited(false)
{

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

const std::map<std::string, Client >& Channel::GetMembers(void)const {
return this->_members;
}

const std::map<std::string, Client >& Channel::GetOps(void)const {
    return this->_Ops;
}

bool Channel::GetBoolPswd(void){
    return paswrd;
}

void Channel::SitBoolPswd(bool is){
    paswrd = is;
}