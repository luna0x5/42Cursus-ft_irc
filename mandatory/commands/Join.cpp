#include "../Inc/Server.hpp"

bool Name_check(std::string line){
    if (line[0] != '#'){
        return false;
    }
    return true;
}

bool    Server::Already_in_channel(Channel &chan, const std::string &nick){
    std::map<std::string, Client>::const_iterator it = chan.GetMembers().find(nick);
    if (it != chan.GetMembers().end()){
        return true;
    }
    return false;
}

// bool    Server::Invite_only(Channel &chan){
//     if (chan.get_l() == true && chan.getCapacityLimit() <= chan.GetMembers().size()){
//     }
//     return false;
// }

int Server::JoinParse(std::vector<std::string> *channels, std::vector<std::string> *keys){
    
    if (this->_line.size()<=1){
        std::cerr<<"Error join"<<std::endl;
        // sendErr(ERR_NEEDMOREPARAMS, "");
        std::cerr<<"ERR_NEEDMOREPARAMS"<<std::endl;
        return 0;
    }
    if (!ft_split(channels, this->_line[1], ',')){
        std::cerr<<"ERR_NEEDMOREPARAMS"<<std::endl;
        // sendErr(ERR_NEEDMOREPARAMS, "");
        return 0;
    }
    if (this->_line.size() == 3 && !ft_split(keys, this->_line[2], ',')){
        // sendErr(ERR_NEEDMOREPARAMS, "");
        std::cerr<<"ERR_NEEDMOREPARAMS"<<std::endl;
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
        // sendErr(ERR_NOTREGISTERED, "");//451
        std::cerr<<"ERR_NOTREGISTERED"<<std::endl;
        return ;
    }
    std::vector<std::string> chans;
    std::vector<std::string> keys;
    if (!JoinParse(&chans, &keys)){
        return ;
    }
    for (size_t i=0; i<chans.size(); i++){
        if (Name_check(chans[i]) == false){
            // sendErr(ERR_NOSUCHCHANNEL, "");
            std::cerr<<"ERR_NOSUCHCHANNEL"<<std::endl;
            continue;
        }
        if (this->_channel.find(chans[i]) == this->_channel.end()){
            this->_channel[chans[i]] = Channel(chans[i]);
            Channel &Chan = this->_channel[chans[i]];
            Client *membr = &this->_client[this->_currentClient];
            Chan.addMember(*membr);
            Chan.addOps(*membr);
            // sendErr(RPL_JOIN, "");
            std::cerr<<"RPL_JOIN"<<std::endl;
        }
        else{
            Channel &Chan = this->_channel[chans[i]];
            Client *membr = &this->_client[this->_currentClient];
            if (Already_in_channel(Chan, membr->getnick())){
                // sendErr(ERR_USERONCHANNEL, "");
                std::cerr<<"ERR_USERONCHANNEL"<<std::endl;
                continue;
            }
            //check if already exist in channel

            std::cout<<Chan.is_userLimited()<< "   ->   " << Chan.getCapacityLimit() <<std::endl;
            if (Chan.is_userLimited() == true && Chan.getCapacityLimit() <= (int)Chan.GetMembers().size()){
                // sendErr(ERR_CHANNELISFULL, "");
                std::cerr<<"ERR_CHANNELISFULL"<<std::endl;
            }
            //invite only
            if (Chan.is_keyed()){
                std::cout<<"key"<<std::endl;
                if ( i < keys.size() && Chan.GetPassword() == keys[i]){
                    Chan.addMember(*membr);
                }
                else {
                    if (i >= keys.size()){
                        // sendErr(ERR_NEEDMOREPARAMS, "");
                        std::cerr<<"ERR_NEEDMOREPARAMS"<<std::endl;
                    }
                    else {
                        // sendErr(ERR_BADCHANNELKEY, "");
                        std::cerr<<"ERR_BADCHANNELKEY"<<std::endl;
                    }
                }
            }
            else {
                std::cout<<"no key"<<std::endl;
                Client *membr = &this->_client[this->_currentClient];
                this->_channel[chans[i]].addMember(*membr);
                // sendErr(RPL_JOIN, "");
                std::cerr<<"RPL_JOIN"<<std::endl;
            }
        }
    }
}
