#include "Server.hpp"

void Server::PASS(void){
	int fd = this->_currentClient;
	std::string nick = this->_client[this->_currentClient].getnick();

	if (this->_client[this->_currentClient].getregistered() || this->_client[this->_currentClient].getisPassed()){
		sendReply(fd, ERR_ALREADYREGISTERED(nick));
		return ;
	}
	if (this->_line.size() < 2){
		sendReply(fd, ERR_NEEDMOREPARAMS(nick, "PASS"));
		return ;
	}
	if ( _line[1] != this->_password){
		sendReply(fd, ERR_PASSWDMISMATCH(std::string("*")));
		return ;
	}
	this->_client[this->_currentClient].setisPassed(1);
	this->_client[this->_currentClient].setreg();
}
