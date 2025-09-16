#include "Server.hpp"

void Server::USER(void){
	// std::cout<<std::endl;
	if (!this->_client[this->_currentClient].getisPassed()){
		std::cout << "error password dismatch------" << std::endl;
		return;
	}
	if (this->_client[this->_currentClient].getregistered()){
		std::cout <<"error already registered-----" << std::endl;
		return;
	}
	if (this->_line.size() != 5){
	for(size_t i=0; i < this->_line.size(); i++){
		std::cout<< "[ " <<this->_line[i] << " ]";
	}
		std::cout << "error needs more params----" << std::endl;
		return;
	}
	this->_client[this->_currentClient].SitUsername(this->_line[2]);
	this->_client[this->_currentClient].setrealname(this->_line[1]);
	this->_client[this->_currentClient].setreg();
	this->_client[this->_currentClient].setFd(this->_currentClient);
	if (this->_client[this->_currentClient].getreg() == 3){
		std::cout << "welcome reply-----" << std::endl;
		return;
	}
}
