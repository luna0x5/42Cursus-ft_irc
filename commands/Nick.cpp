#include "Server.hpp"

bool Server::AlreadyInUse(void){
	std::map<int, Client>::iterator it = this->_client.begin();
	for(size_t i = 0; i < this->_client.size(); i++){
		if (it->second.getnick() == this->_line[1]){
			return false;
		}
		std::advance(it,1);
	}
	return true;
}

bool Server::firstChar(void){
	std::string except = "QWERTYUIOPLKJHGFDSAZXCVBNMqwertyuioplkjhgfdsazxcvbnm[]\\`_^{|}";
	return(except.find(this->_line[1][0]) != std::string::npos);
}

bool Server::otherChar(void){
	std::string except = "QWERTYUIOPLKJHGFDSAZXCVBNMqwertyuioplkjhgfdsazxcvbnm[]\\`_^{|}123456789-";
	for (size_t i=1; i < this->_line[i].length(); i++){
		if (except.find(this->_line[1][i]) == std::string::npos){
			return false;
		}
	}
	return true;
}

bool Server::Nickparse(void){
	if (this->_line[1].size() < 1 || this->_line[1].size()>=9){
		return false;
	}
	if (!firstChar() || !otherChar()){
		return false;
	}
	return true;
}

void Server::NICK(void){
	if (!this->_client[this->_currentClient].getisPassed()){
		std::cout << "Password error-------" << std::endl;
		OneClean();
		return;
	}
	if (!AlreadyInUse()){
		std::cout << "nickname error-------" << std::endl;
		OneClean();
		return;
	}
	if (!Nickparse()){
		std::cout << "no such nickname-----" << std::endl;
		OneClean();
		return;
	}
	this->_client[this->_currentClient].setnick(this->_line[1]);
	this->_client[this->_currentClient].setreg();
	if (this->_client[this->_currentClient].getreg() == 3){
		sendReply(this->_client[_currentClient].getFd(), "welcome reply------");
		return;
	}
	// std::cout<<"nickname : "<< this->_client[this->_currentClient].getnick()<<std::endl;
}
