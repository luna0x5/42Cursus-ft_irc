#include "Server.hpp"

void Server::USER(void){
	// std::cout<<std::endl;
	if (!this->_client[this->_currentClient].getisPassed()){
		sendErr(ERR_PASSWDMISMATCH, "");
		return;
	}
	if (this->_client[this->_currentClient].getregistered()){
		sendErr(ERR_ALREADYREGISTERED, "");
		return;
	}
	if (this->_line.size() != 5){
	for(size_t i=0; i < this->_line.size(); i++){
		std::cout<< "[ " <<this->_line[i] << " ]";
	}
		sendErr(ERR_NEEDMOREPARAMS, "");
		return;
	}
	this->_client[this->_currentClient].SitUsername(this->_line[2]);
	this->_client[this->_currentClient].setrealname(this->_line[1]);
	this->_client[this->_currentClient].setreg();
	this->_client[this->_currentClient].setFd(this->_currentClient);
	if (this->_client[this->_currentClient].getreg() == 3){
		sendErr(RPL_WELCOME, "");
		return;
	}
}
