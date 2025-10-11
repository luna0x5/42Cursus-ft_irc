#include "../server/Server.hpp"

// #include "Server.hpp"

void Server::PASS(void){
	int fd = this->_currentClient;
	std::string nick = this->_client[fd].getnick();

	if (this->_client[fd].getisPassed()){
		sendReply(fd, ERR_ALREADYREGISTERED(nick));
		return ;
	}
	if (this->_line.size() < 2){
		sendReply(fd, ERR_NEEDMOREPARAMS(nick, "PASS"));
		return ;
	}
	if ( _line[1] != this->_password){
		sendReply(fd, ERR_PASSWDMISMATCH);
		return ;
	}
	this->_client[fd].setisPassed(1);
	// this->_client[fd].setreg();
}
