#include "Server.hpp"

void Server::PASS(void){
	if (this->_client[this->_currentClient].getregistered() || this->_client[this->_currentClient].getisPassed()){
		std::cout << "this client is already" << std::endl;
		return ;
	}
	if (this->_line.size() < 2){
		std::cout << "you need more params" << std::endl;
		return ;
	}
	if ( _line[1] != this->_password){
		std::cout << "password is wrong" <<std::endl;
		return ;
	}
	this->_client[this->_currentClient].setisPassed(1);
	this->_client[this->_currentClient].setreg();
}
