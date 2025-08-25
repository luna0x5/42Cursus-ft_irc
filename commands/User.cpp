#include "../server/Server.hpp"

void Server::USER(void){
	// for(size_t i=0; i < this->_line.size(); i++){
	// 	std::cout<< "[ " <<this->_line[i] << " ]";
	// }
	// std::cout<<std::endl;
	if (!this->_client[this->_currentClient].getisPassed()){
		std::cerr<<"ERR_PASSWDMISMATCH (464"<<std::endl;
		return;
	}
	if (this->_client[this->_currentClient].getregistered()){
		std::cerr<<"ERR_ALREADYREGISTERED (462)"<<std::endl;
		return;
	}
	if (this->_line.size() != 5){
		std::cerr<<"ERR_NEEDMOREPARAMS "<<std::endl;
		return;
	}
	this->_client[this->_currentClient].SitUsername(this->_line[2]);
	this->_client[this->_currentClient].setrealname(this->_line[1]);
	this->_client[this->_currentClient].setreg();
	if (this->_client[this->_currentClient].getreg() == 3){
		Sender("001 ");
		return;
	}
}
