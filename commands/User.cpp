#include "Server.hpp"

void Server::USER(void){
	int	fd = this->_currentClient;
	if (!this->_client[fd].getisPassed()){
		sendReply(fd, ERR_PASSWDMISMATCH);
		return;
	}
	// if (this->_client[fd].getregistered()){
	// 	sendReply(fd, ERR_ALREADYREGISTERED(this->_client[fd].getnick()));
	// 	return;
	// }
	if (this->_line.size() != 5){
	for(size_t i=0; i < this->_line.size(); i++){
		std::cout<< "[ " <<this->_line[i] << " ]";
	}
		sendReply(fd, ERR_NEEDMOREPARAMS(this->_client[fd].getnick(), "USER"));
		return;
	}
	this->_client[fd].SitUsername(this->_line[2]);
	this->_client[fd].setrealname(this->_line[1]);
	// this->_client[fd].setreg();
	this->_client[fd].setFd(fd);
	this->_client[fd].set_is_user(1);
	if (this->_client[fd].get_is_nick() == 1){
		this->_client[fd].setregistered(1);
		sendReply(fd, RPL_WELCOME(this->_client[fd].getnick()));
		return;
	}
}
