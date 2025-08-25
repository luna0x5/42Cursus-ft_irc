#include "../server/Server.hpp"

void Server::PASS(void){
	if (this->_client[this->_currentClient].getregistered()){
		std::cerr<<"ERR_ALREADYREGISTRED"<<std::endl; // we will thrown it
		return ;
	}
	if (this->_line.size() < 2){
		std::cerr<<"ERR_NEEDMOREPARAMS (461)"<<std::endl;
		return ;
	}
	if ( _line[1] != this->_password){
		std::cout<<_line[1]<<std::endl;
		std::cerr<<"ERR_PASSWDMISMATCH (464)"<<std::endl; //replies
		return ;
	}
	this->_client[this->_currentClient].setisPassed(1);
	this->_client[this->_currentClient].setreg();
}
