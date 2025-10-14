#include "Client.hpp"

Client::Client():isPassed(0),registered(0){

}

Client::~Client(){
    
}

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
    
    while ((pos = Buffer.find("\n")) != std::string::npos) { // WE WILL USE "\r\n" when we will use limechat
        std::string command = Buffer.substr(0, pos);
        
        if (!command.empty()) {
            cmds.push_back(command);
        }
        Buffer.erase(0, pos + 2);
    }
} // if the \r\n exactement in the end what find will return in buffer if it's empty
 std::string& Client::GetUsername(void){
    return username;
}

void Client::SitUsername(std::string user){
    username = user;
}

bool Client::getregistered(void){
    return this->registered;
}

////////////////////////////

bool Client::getisPassed(void){
    return this->isPassed;
}

void Client::setisPassed(bool p){
    this->isPassed = p;
}

void Client::set_is_user(bool u){
    this->isUser = u;
}
bool Client::get_is_user(void){
    return this->isUser;
}
bool Client::get_is_nick(void){
    return this->isNick;
}
void Client::set_is_nick(bool n){
    this->isNick = n;
}

/////////////////////////////////

void Client::setregistered(bool r){
    this->registered = r;
}

// void Client::setreg(void){
//     this->reg_done++;
// }

// int Client::getreg(void){
//     return this->reg_done;
// }

std::string Client::getnick(void){
    return this->nickname;
}
void Client::setnick(std::string nick){
    this->nickname = nick;
}
std::string Client::getuser(void){
    return this->username;
}
void Client::setuser(std::string user){
    this->username = user;
}
void Client::setrealname(std::string real){
    this->realname = real.erase(0,1);
}
std::string Client::getrealname(void){
    return this->realname;
}

void
Client::setFd(int fd)
{
    this->_fd = fd;
}

int
Client::getFd( void ) const
{
    return this->_fd;
}
