#include "Server.hpp"

// int Server::JoinParse(std::vector<std::string> *channels, std::vector<std::string> *keys){
    
//     if (this->_line.size()<=1 || this->_line.size()>3){
//         std::cerr<<"Error join"<<std::endl;
//         return 0;
//     }
//     if (!ft_split(channels, this->_line[1], ',')){
//         std::cerr<<"specific replies"<<std::endl;
//         return 0;
//     }
//     if (this->_line.size() == 3 && !ft_split(keys, this->_line[2], ',')){
//         std::cerr<<"specific replies"<<std::endl;
//         return 0;
//     }
//     if ((*channels).size() < (*keys).size()){
//         std::cerr<<"keys more that channels"<<std::endl;
//     }
//     return 1;
// }

// int Server::ft_split(std::vector<std::string> *channels, std::string& chans, char delimiter){
//     std::stringstream line(chans);
//     if (chans[chans.find_last_not_of(" \t") ] == delimiter){return 0;}
//     std::string chan;
//     while(std::getline(line, chan, delimiter)){
//         chan.erase(0, chan.find_first_not_of(" \t"));
//         chan.erase(chan.find_last_not_of(" \t") + 1);
//         if (!chan.empty()){
//             (*channels).push_back(chan);
//             chan.clear();
//         }
//         else{#include "Server.hpp"

// int Server::JoinParse(std::vector<std::string> *channels, std::vector<std::string> *keys){
    
//     std::string nick    = this->_client[this->_currentClient].getnick();
//     int         fd      = this->_currentClient;

//     if (this->_line.size()<=1){
//         std::cerr<<"Error join"<<std::endl;
//         sendReply(fd, ERR_NEEDMOREPARAMS(nick, "JOIN"));
//         return 0;
//     }
//     if (!ft_split(channels, this->_line[1], ',')){
//         sendReply(fd, ERR_NEEDMOREPARAMS(nick, "JOIN"));
//         // std::cerr<<"specific replies"<<std::endl;
//         return 0;
//     }
//     if (this->_line.size() == 3 && !ft_split(keys, this->_line[2], ',')){
//         sendReply(fd, ERR_NEEDMOREPARAMS(nick, "JOIN"));
//         return 0;
//     }
//     // if ((*channels).size() < (*keys).size()){
//     //     std::cerr<<"keys more that channels"<<std::endl;
//     // }
//     return 1;
// }

// int Server::ft_split(std::vector<std::string> *channels, std::string& chans, char delimiter){
//     std::stringstream line(chans);
//     if (chans[chans.find_last_not_of(" \t") ] == delimiter){return 0;}
//     std::string chan;
//     while(std::getline(line, chan, delimiter)){
//         chan.erase(0, chan.find_first_not_of(" \t"));
//         chan.erase(chan.find_last_not_of(" \t") + 1);
//         if (!chan.empty()){
//             (*channels).push_back(chan);
//             chan.clear();
//         }
//         else{
//             // sendReply(ERR_NEEDMOREPARAMS, "");
//             // std::cerr<<"Error parsing in join"<<std::endl;
//             chans.clear();
//             return 0;
//         }
//     }
//     chans.clear();
//     return 1;
// }

// int Server::IsChannelExist(std::string ChanName){
//     for(size_t i=0; i < this->_channel.size(); i++){
//         if (this->_channel[i].GetName() == ChanName){
//             return i + 1;
//         }
//     }
//     return 0;
// }

// void Server::JOIN(void){
//     std::vector<std::string> chans;
//     std::vector<std::string> keys;
//     if (!JoinParse(&chans, &keys)){
//         return ;
//     }
//     // for(size_t i=0; i< chans.size(); i++){
//     //     std::cerr<<"channel : "<<chans[i]<<std::endl;
//     // }
//     // for(size_t i=0; i< keys.size(); i++){
//     //     std::cerr<<"key : "<< keys[i]<<std::endl;
//     // }
        
//     std::string nick    = this->_client[this->_currentClient].getnick();
//     int         fd      = this->_currentClient;

//     for (size_t i=0; i<chans.size(); i++){
//         size_t index = IsChannelExist(chans[i]);
//         if (index <= 0){ // channel doesn't exist in _channel vector
//             Channel Chan;
//             Client *membr = &this->_client[this->_currentClient];
//             Chan.SetName(chans[i]);
//             Chan.GetMembers().push_back(*membr);
//             Chan.GetOps().push_back(*membr);
//             this->_channel.push_back(Chan); // limits of channel in server
//             // std::cout<<Chan.GetName()<<std::endl;
//             sendReply(fd, RPL_JOIN(nick, chans[i]));
//             return ;
//         }
//         else{ //channel exist // check for active bans and if it invite only 
//             if (this->_channel[index - 1].GetBoolPswd()){ // channel with password
//                 if ( i < keys.size() && this->_channel[index-1].GetPassword() == keys[i]){ // i position of channel in command line
//                     Client *membr = &this->_client[this->_currentClient]; // index position of exist channel in channel vector
//                     this->_channel[index - 1].GetMembers().push_back(*membr);
//                     // std::cout<<"channel exist with correct password"<<std::endl;
//                     // sendReply(fd, RPL_JOIN(nick, ));//put channel name after fixing struct
//                 }
//                 else {
//                     if (i >= keys.size()){
//                         // std::cout<<"specific reply for no password"<<std::endl;
//                         sendReply(fd, ERR_NEEDMOREPARAMS(nick, "JOIN"));
//                         return ;
//                     }
//                     else {
//                         // sendReply(fd, ERR_BADCHANNELKEY(nick, ));//put channel name after fixing struct
//                         return ;
//                         // std::cout<<"specific reply for password not matched"<<std::endl;
//                     }
//                 }
//             }
//             else { 
//                 Client *membr = &this->_client[this->_currentClient];
//                 this->_channel[index - 1].GetMembers().push_back(*membr);
//                 std::cout<<"channel exist witout password : "<<this->_channel[index - 1].GetName()<<std::endl;
//                 // sendReply(fd, RPL_JOIN(nick, chans[i]));//put channel name after fixing struct
//             }
//         }
//     }
// }
