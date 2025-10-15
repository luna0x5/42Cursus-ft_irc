#include "Server.hpp"

void Server::USER(void){
	int	fd = this->_currentClient;
	// std::cout<<std::endl;
	if (!this->_client[this->_currentClient].getisPassed()){
		sendReply(fd, ERR_PASSWDMISMATCH(std::string("*")));
		return;
	}
	if (this->_client[this->_currentClient].getregistered()){
		sendReply(fd, ERR_ALREADYREGISTERED(this->_client[this->_currentClient].getnick()));
		return;
	}
	if (this->_line.size() != 5){
	for(size_t i=0; i < this->_line.size(); i++){
		std::cout<< "[ " <<this->_line[i] << " ]";
	}
		sendReply(fd, ERR_NEEDMOREPARAMS(this->_client[this->_currentClient].getnick(), "USER"));
		return;
	}
	this->_client[this->_currentClient].SitUsername(this->_line[2]);
	this->_client[this->_currentClient].setrealname(this->_line[1]);
	this->_client[this->_currentClient].setreg();
	this->_client[this->_currentClient].setFd(this->_currentClient);
	if (this->_client[this->_currentClient].getreg() == 3){
		sendReply(fd, RPL_WELCOME(this->_client[this->_currentClient].getnick()));
		return;
	}
}
