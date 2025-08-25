#include "../server/Server.hpp"

int Server::JoinParse(std::vector<std::string> *channels, std::vector<std::string> *keys){
    
    if (this->_line.size()<=1 || this->_line.size()>3){
        std::cerr<<"Error join"<<std::endl;
        return 0;
    }
    if (!split(channels, this->_line[1], ',')){
        std::cerr<<"specific replies"<<std::endl;
        return 0;
    }
    if (this->_line.size() == 3 && !split(keys, this->_line[2], ',')){
        std::cerr<<"specific replies"<<std::endl;
        return 0;
    }
    if ((*channels).size() < (*keys).size()){
        std::cerr<<"keys more that channels"<<std::endl;
    }
    return 1;
}

int Server::split(std::vector<std::string> *channels, std::string& chans, char delimiter){
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
            std::cerr<<"Error parsing in join"<<std::endl;
            chans.clear();
            return 0;
        }
    }
    chans.clear();
    return 1;
}

int Server::IsChannelExist(std::string ChanName){
    for(size_t i=0; i < this->_channel.size(); i++){
        if (this->_channel[i].GetName() == ChanName){
            return i + 1;
        }
    }
    return 0;
}

void Server::JOIN(void){
    std::vector<std::string> chans;
    std::vector<std::string> keys;
    JoinParse(&chans, &keys);
    // for(size_t i=0; i< chans.size(); i++){
    //     std::cerr<<"channel : "<<chans[i]<<std::endl;
    // }
    // for(size_t i=0; i< keys.size(); i++){
    //     std::cerr<<"key : "<< keys[i]<<std::endl;
    // }
    for (size_t i=0; i<chans.size(); i++){
        size_t index = IsChannelExist(chans[i]);
        if (index <= 0){
            Channel Chan;
            Client *membr = &this->_client[this->_currentClient];
            Chan.SetName(chans[i]);
            Chan.GetMembers().push_back(*membr);
            Chan.GetOps().push_back(*membr);
            this->_channel.push_back(Chan);
            std::cout<<Chan.GetName()<<std::endl;
        }
        else{
            if (this->_channel[index - 1].GetBoolPswd()){
                if ( i < keys.size() && this->_channel[index-1].GetPassword() == keys[i]){
                    Client *membr = &this->_client[this->_currentClient];
                    this->_channel[index - 1].GetMembers().push_back(*membr);
                    std::cout<<"channel exist with correct password"<<std::endl;
                }
                else {
                    if (i >= keys.size()){
                        std::cout<<"specific reply for no password"<<std::endl;
                    }
                    else {
                        std::cout<<"specific reply for password not matched"<<std::endl;
                    }
                }
            }
            else {
                Client *membr = &this->_client[this->_currentClient];
                this->_channel[index - 1].GetMembers().push_back(*membr);
                std::cout<<"channel exist witout password : "<<this->_channel[index - 1].GetName()<<std::endl;
            }
        }
    }
}
