#include "../server/Server.hpp"

// #include "Server.hpp"

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
	for (size_t i=1; i < this->_line[1].size(); i++){
		std::cout<<"["<< this->_line[1]<< "] : " << "("<< this->_line[1][i]<< ")  : " <<i<< "  :  "<< this->_line[i].size() <<std::endl;
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
		std::cout<<"here"<<std::endl;
		return false;
	}
	return true;
}

void Server::NICK(void){
	int fd = this->_currentClient;
	// std::string nick = this->_client[this->_currentClient].getnick();

	if (!this->_client[fd].getisPassed()){
		sendReply(fd, ERR_PASSWDMISMATCH);
		// OneClean();
		return;
	}
	if (!AlreadyInUse()){
		sendReply(fd, ERR_NICKNAMEINUSE);
		// OneClean();
		return;
	}
	if (!Nickparse()){
		sendReply(fd, ERR_ERRONEUSNICKNAME);
		// OneClean();
		return;
	}
	this->_client[fd].setnick(this->_line[1]);
	this->_client[fd].set_is_nick(1);
	if (this->_client[fd].get_is_user()){
		this->_client[fd].setregistered(1);
		sendReply(fd, RPL_WELCOME(this->_line[1]));
		return;
	}
	// std::cout<<"nickname : "<< this->_client[this->_currentClient].getnick()<<std::endl;
}

//nick + no params
