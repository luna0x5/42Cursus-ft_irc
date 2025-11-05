#include "Server.hpp"

bool checker(std::string s){
	for(size_t i = 0; i < s.size(); i++){
		if (!isalnum(s[i]) && s[i] != '-' && s[i] != '_'){
			return false;
		}
	}
	return true;
}

void Server::USER(void){
	// for(size_t i=0; i < this->_line.size(); i++){
	// 	std::cout<< "[ " <<this->_line[i] << " ]";
	// }
	// std::cout<<std::endl;
	// std::cout<<this->_line[0] << std::endl;
	// std::cout<<this->_line[1] << std::endl;
	// std::cout<<this->_line[2] <<std::endl;
	// std::cout<<this->_line[3] <<std::endl;
	// std::cout<<this->_line[4] <<std::endl;
	int	fd = this->_currentClient;
	if (!this->_client[fd].getisPassed()){
		sendReply(fd, ERR_NOTREGISTERED(this->_client[fd].getnick()));
		std::cerr << "sent => ERR_NOTREGISTERED." << std::endl;
		return;
	}
	if (this->_client[fd].getregistered()){
		sendReply(fd, ERR_ALREADYREGISTERED(this->_client[fd].getnick()));
		std::cerr << "sent => ERR_ALREADYREGISTERED." << std::endl;
		return;
	}
	if (this->_line.size() != 5){
		sendReply(fd, ERR_NEEDMOREPARAMS(this->_client[fd].getnick(), "USER"));
		std::cerr << "sent => ERR_NEEDMOREPARAMS." << std::endl;
		std::cerr << "user1" << std::endl;
		return;
	}
	if (this->_line[2].length() > 12){
		sendReply(fd, ERR_NEEDMOREPARAMS(this->_client[fd].getnick(), "USER"));
		std::cerr << "sent => ERR_NEEDMOREPARAMS." << std::endl;
		std::cerr << "user2" << std::endl;
		return;
	}
	if (!checker(this->_line[2])){
		sendReply(fd, ERR_NEEDMOREPARAMS(this->_client[fd].getnick(), "USER"));
		std::cerr << "sent => ERR_NEEDMOREPARAMS." << std::endl;
		std::cerr << "user3" << std::endl;
		return;
	}
	// if (this->_line[3] != "0"){
	// 	sendReply(fd, ERR_NEEDMOREPARAMS(this->_client[fd].getnick(), "USER"));
	// 	std::cerr << "sent => ERR_NEEDMOREPARAMS." << std::endl;
		// std::cerr << "user4" << std::endl;
	// 	return;
	// }
	// if (this->_line[1][0] != ':'){
	// 	sendReply(fd, ERR_NEEDMOREPARAMS(this->_client[fd].getnick(), "USER"));
	// 	std::cerr << this->_line[1] << std::endl;
	// 	std::cerr << "user5" << std::endl;
	// 	return;
	// }
	this->_client[fd].SitUsername(this->_line[2]);
	this->_client[fd].setrealname(this->_line[1]);
	this->_client[fd].setFd(fd);
	this->_client[fd].set_is_user(1);
	if (this->_client[fd].get_is_nick() == 1){
		this->_client[fd].setregistered(1);
		sendReply(fd, RPL_WELCOME(this->_client[fd].getnick()));
		std::cerr << "sent => RPL_WELCOME." << std::endl;
		return;
	}
}
