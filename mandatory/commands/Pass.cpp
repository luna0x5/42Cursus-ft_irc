#include "Server.hpp"

void Server::PASS(void){
	int fd = this->_currentClient;
	std::string nick = this->_client[fd].getnick();

	if (this->_client[fd].getisPassed()){
		sendReply(fd, ERR_ALREADYREGISTERED(nick));
		std::cerr << "sent => ERR_ALREADYREGISTERED." << std::endl;
		return ;
	}
	if (this->_line.size() < 2){
		sendReply(fd, ERR_NEEDMOREPARAMS(nick, "PASS"));
		std::cerr << "sent => ERR_NEEDMOREPARAMS." << std::endl;

		return ;
	}
	if ( _line[1] != this->_password){
		sendReply(fd, ERR_PASSWDMISMATCH(std::string("*")));
		std::cerr << "sent => ERR_PASSWDMISMATCH." << std::endl;
		return ;
	}
	this->_client[fd].setisPassed(1);
	// this->_client[fd].setreg();
}
