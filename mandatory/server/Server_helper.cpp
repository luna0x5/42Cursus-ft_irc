#include "Server.hpp"
#include "Channel.hpp"

void
Server::handle_new_connections(int Socket_fd)
{
    sockaddr_in clientAdress;
    socklen_t   len = sizeof(clientAdress);

    int         new_socket = accept(Socket_fd, (struct sockaddr *) &clientAdress, &len);//accepting the incoming request 
    checkErr(new_socket, -1, "failed to accept new connection!");
    std::cout << "client connected" << std::endl;

    checkErr(fcntl(new_socket, F_SETFL, O_NONBLOCK), -1, "failed to add file flags!");

    pollfd new_fd;
    new_fd.fd = new_socket;
    new_fd.events = POLLIN;
    this->_poll_fds.push_back(new_fd);
    this->_client[new_fd.fd] = Client();
}

void Server::handle_client_data(int fd){
    this->_currentClient = fd;
    std::vector<std::string>& cmd = this->_client[fd].getCmds();
    for(size_t i=0; i< cmd.size(); i++){
        parse_cmd(cmd[i]);
    }
    cmd.clear();
}

void Server::initCmds(void){
    this->_cmd["PASS"] = PASS_cmd;
    this->_cmd["NICK"] = NICK_cmd;
    this->_cmd["USER"] = USER_cmd;
    this->_cmd["JOIN"] = JOIN_cmd;
    this->_cmd["PART"] = PART_cmd;
    this->_cmd["MODE"] = MODE_cmd;
    this->_cmd["TOPIC"] = TOPIC_cmd;
    this->_cmd["KICK"] = KICK_cmd;
    this->_cmd["INVITE"] = INVITE_cmd;
    this->_cmd["/BOT"] = BOT_CMD;
}

int Server::GetCmds(void){
    std::map<std::string, Commands>::iterator it = this->_cmd.find(this->_line[0]);
    if (it != this->_cmd.end()){
        return it->second;
    }
    return UNKNOWN_cmd;
}

void Server::commands_handler(){
    int cmd = GetCmds();
    switch (cmd){
        case 0:
            PASS();
            break;
        case 1:
            NICK();
            break;
        case 2:
            USER();
            break;
        case 3:
            JOIN();
            break;
        case 4:
            std::cout<<"PART"<<std::endl;
            break;
        case 5:
            MODE();
            break;
        case 6:
            std::cout<<"TOPIC"<<std::endl;
            break;
        case 7:
            std::cout<<"KICK"<<std::endl;
            break;
        case 8:
            std::cout<<"INVITE"<<std::endl;
            break;
        case 9:
            this->BOT();
            break;
        default:{
            std::cout<<"UNKNOWN : ";
                for(size_t i=0; i< _line.size(); i++){
                std::cout<< this->_line[i] << " ";
                }
                std::cout<<std::endl;
        }
    }
    this->_line.clear();
}

void Server::parse_cmd(std::string cmd){

    std::string message;
    std::string prefix;
    std::string command;
    std::string target;
    size_t      pos = cmd.find(" :");

    if (pos != std::string::npos){
        message = cmd.substr(pos + 1);
        cmd.erase(pos);
    }
    std::stringstream bf(cmd);
    if (cmd[0] == ':'){
        bf>>prefix;
        prefix.erase(0,1);
    }
    bf>>command;
    if (!command.empty()){
        this->_line.push_back(command);
    }
    if (!message.empty()){
        this->_line.push_back(message);
    }
    if (!prefix.empty()){
        this->_line.push_back(prefix);
    }
    while(bf>>target){
        if (!target.empty()){
            this->_line.push_back(target);
        }
    }
    commands_handler();
}

// void Server::Sender(std::string num){
//     std::string to_client   = ":localhost" + num + this->_client[this->_currentClient].getnick() + " :Welcome to our server\r\n";
//     int         bytes       = send(this->_currentClient, to_client.c_str(), to_client.length(), 0);
//     if(bytes < 0){
//         std::cerr<<"failed send data "<<std::endl;
//     }
// }

void Server::cleaner(void){
    for(size_t i=0; i < this->_poll_fds.size(); i++){
        close(this->_poll_fds[i].fd);
        _client.erase(this->_poll_fds[i].fd);
        this->_poll_fds.erase(this->_poll_fds.begin() + i);
        i--;
    }
    exit(1);
}

// void Server::sendReply(const reply code, const std::string cmdName){
//     // thsi function append errors and replies to the client's buffer

//     std::string reply = ":localhost " 
//                          + code.code + " "
//                         + cmdName + " "
//                         + this->_client[this->_currentClient].getnick()
//                         + " :" + code.msg + "\r\n";
//             send(this->_currentClient, reply.c_str(), reply.length(), 0);
//     // size_t bytes = send(this->_currentClient, reply.c_str(), reply.length(), 0);

//     // if(bytes < 0){
//     //     std::cerr<<"failed send data "<<std::endl;
//     // }
// }

void
Server::sendReply(int fd, const std::string& reply)
{
    
    int         bytes = send(fd, reply.c_str(), reply.length(), 0);
    if(bytes < 0)
        std::cerr<<"Error: Failed send data !"<<std::endl;
}

bool Server::findit(pollfd p){
    return (p.fd == this->_currentClient);
}

void        Server::OneClean(void){
    // shutdown(this->_currentClient, SHUT_RDWR);
    close(this->_currentClient);
    this->_client.erase(this->_currentClient);
    for(size_t i=0; i < this->_poll_fds.size(); i++){
        if (this->_poll_fds[i].fd == this->_currentClient){
            this->_poll_fds.erase(this->_poll_fds.begin() + i);
            break;
        }
    }

}
