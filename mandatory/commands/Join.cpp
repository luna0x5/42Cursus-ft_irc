#include "../Inc/Server.hpp"

bool Name_check(std::string line){
    if (line[0] != '#'){
        return false;
    }
    return true;
}


int Server::JoinParse(std::vector<std::string> *channels, std::vector<std::string> *keys){
    
    if (this->_line.size()<=1){
        sendReply(this->_currentClient, ERR_NEEDMOREPARAMS(this->_client[this->_currentClient].getnick(), "JOIN"));
        std::cerr<<"sent => ERR_NEEDMOREPARAMS."<<std::endl;
        return 0;
    }
    if (!ft_split(channels, this->_line[1], ',')){
        std::cerr<<"sent => ERR_NEEDMOREPARAMS."<<std::endl;
        sendReply(this->_currentClient, ERR_NEEDMOREPARAMS(this->_client[this->_currentClient].getnick(), "JOIN"));
        return 0;
    }
    if (this->_line.size() == 3 && !ft_split(keys, this->_line[2], ',')){
        sendReply(this->_currentClient, ERR_NEEDMOREPARAMS(this->_client[this->_currentClient].getnick(), "JOIN"));
        std::cerr<<"sent => ERR_NEEDMOREPARAMS."<<std::endl;
        return 0;
    }
    return 1;
}

int Server::ft_split(std::vector<std::string> *channels, std::string& chans, char delimiter){
    std::stringstream line(chans);
    if (chans[chans.find_last_not_of(" \t") ] == delimiter){return 0;}
    std::string chan;
    while(std::getline(line, chan, delimiter)){
        chan.erase(0, chan.find_first_not_of(" \t"));
        chan.erase(chan.find_last_not_of(" \t") + 1);
        if (!chan.empty()){
            (*channels).push_back(chan);
            chan.clear();
        }
        else{
            chans.clear();
            return 0;
        }
    }
    chans.clear();
    return 1;
}
void Server::JOIN(void){
    if (!this->_client[this->_currentClient].getregistered()){
        sendReply(this->_currentClient, ERR_NOTREGISTERED(this->_client[this->_currentClient].getnick()));
        std::cerr<<"sent => ERR_NOTREGISTERED."<<std::endl;
        return ;
    }
    std::vector<std::string> chans;
    std::vector<std::string> keys;
    if (!JoinParse(&chans, &keys)){
        return ;
    }
    for (size_t i=0; i<chans.size(); i++){
        std::string message = ":" + this->_client[this->_currentClient].getPrefix() + " JOIN " + chans[i] + "\r\n";
        if (Name_check(chans[i]) == false){
            sendReply(this->_currentClient, ERR_NOSUCHCHANNEL(this->_client[this->_currentClient].getnick(), chans[i]));
            std::cerr<<"sent => ERR_NOSUCHCHANNEL."<<std::endl;
            continue;
        }
        if (this->_channel.find(chans[i]) == this->_channel.end()){
            Channel &Chan = this->_channel[chans[i]];
            Client *membr = &this->_client[this->_currentClient];
            this->_channel[chans[i]] = Channel(chans[i]);
            Chan.addMember(membr);
            Chan.addOps(membr);
            Chan.broadcastReply(message);
            std::cerr<<"sent => RPL_JOIN."<<std::endl;
            sendReply(this->_currentClient, Chan.displayInfo(membr->getnick()));
        }
        else{
            Channel &Chan = this->_channel[chans[i]];
            Client *membr = &this->_client[this->_currentClient];
            if (Chan.is_Member(membr->getnick())){
                std::cout<< "--> " <<membr->getnick()<< " :  " << Chan.is_Op(membr->get_fd()) <<std::endl;
                continue;
            }
            
            if (Chan.is_userLimited() == true && Chan.getCapacityLimit() <= (int)Chan.GetMembers().size()){
                sendReply(this->_currentClient, ERR_CHANNELISFULL(membr->getnick(), Chan.GetName()));
                std::cerr<<"sent => ERR_CHANNELISFULL."<<std::endl;
                continue;
            }
            if (Chan.is_inviteOnly() == true && !Chan.isInvited(membr->getnick())){
                sendReply(this->_currentClient, ERR_INVITEONLYCHAN(membr->getnick(), Chan.GetName()));
                continue;
            }
            if (Chan.is_keyed()){
                if ( i < keys.size() && Chan.GetPassword() == keys[i]){
                    Chan.addMember(membr);
                    std::cerr<<"sent => RPL_JOIN."<<std::endl;
                    Chan.broadcastReply(message);
                    sendReply(this->_currentClient, Chan.displayInfo(membr->getnick()));
                }
                else {
                        sendReply(this->_currentClient, ERR_BADCHANNELKEY(membr->getnick(), Chan.GetName()));
                        std::cerr<<"sent => ERR_BADCHANNELKEY"<<std::endl;
                    }
            }
            else {
                Client *membr = &this->_client[this->_currentClient];
                this->_channel[chans[i]].addMember(membr);
                Chan.broadcastReply(message);
                std::cerr<<"sent => RPL_JOIN."<<std::endl;
                sendReply(this->_currentClient, Chan.displayInfo(membr->getnick()));
            }
        }
    }
}
