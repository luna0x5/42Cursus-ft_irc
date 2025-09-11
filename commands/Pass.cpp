#include "Server.hpp"

void Server::PASS(void){
	if (this->_client[this->_currentClient].getregistered() || this->_client[this->_currentClient].getisPassed()){
		sendErr(ERR_ALREADYREGISTERED, "");
		return ;
	}
	if (this->_line.size() < 2){
		sendErr(ERR_NEEDMOREPARAMS, "");
		return ;
	}
	if ( _line[1] != this->_password){
		sendErr(ERR_PASSWDMISMATCH, "");
		return ;
	}
	this->_client[this->_currentClient].setisPassed(1);
	this->_client[this->_currentClient].setreg();
}
