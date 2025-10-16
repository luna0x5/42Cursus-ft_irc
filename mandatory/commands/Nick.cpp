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
	for (size_t i=1; i < this->_line[1].size(); i++){
		if (except.find(this->_line[1][i]) == std::string::npos){
			return false;
		}
	}
	return true;
}

bool Server::Nickparse(void){
	if (this->_line[1].size() < 1 || this->_line[1].size()>9){
		return false;
	}
	if (!firstChar() || !otherChar()){
		return false;
	}
	return true;
}

void Server::NICK(void){
	int fd = this->_currentClient;

	if (this->_line.size() < 2){
        // sendReply(fd, ERR_NONICKNAMEGIVEN);
		std::cout<<"NICK : no params"<<std::endl;
        return;
    }

	if (!this->_client[fd].getisPassed()){
		// sendReply(fd, ERR_PASSWDMISMATCH);
		// OneClean();
		return;
	}
	std::string	nick("*");
	if (this->_client[fd].getregistered() == false)
		nick = this->_client[fd].getnick();
	if (!AlreadyInUse()){
		sendReply(fd, ERR_NICKNAMEINUSE(nick, this->_line[1]));
		// OneClean();
		return;
	}
	if (!Nickparse()){
		sendReply(fd, ERR_ERRONEUSNICKNAME(nick, this->_line[1]));
		// OneClean();
		return;
	}
	this->_client[fd].setnick(this->_line[1]);
	this->_client[fd].set_is_nick(1);
	if (this->_client[fd].get_is_user() == 1 && this->_client[fd].getregistered() == 0){
		this->_client[fd].setregistered(1);
		sendReply(fd, RPL_WELCOME(this->_line[1]));
		return;
	}

}

//nick + no params