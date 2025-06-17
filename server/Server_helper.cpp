#include "Server.hpp"

void Server::handle_new_connections(int Socket_fd){
    sockaddr_in clientAdress;
    socklen_t len = sizeof(clientAdress);
    int new_socket = accept(Socket_fd, (struct sockaddr *) &clientAdress, &len);
    if (new_socket < 0){
        return ;
    }
    std::cout<<"client connected"<<std::endl;
    int flags = fcntl(new_socket, F_GETFL, 0);
    fcntl(new_socket, F_SETFL, flags | O_NONBLOCK);
    pollfd new_fd;
    new_fd.fd = new_socket;
    new_fd.events = POLLIN;
    poll_fds.push_back(new_fd);
    client[new_fd.fd] = Client();
}

void Server::handle_client_data(int fd){
    std::vector<std::string>& cmd = client[fd].getCmds();
    for(size_t i=0; i< cmd.size(); i++){
        parse_cmd(cmd[i]);
    }
    cmd.clear();
}

void Server::initCmds(void){
    cmd["PASS"] = PASS_cmd;//try catch throw

    cmd["NICK"] = NICK_cmd;
    cmd["USER"] = USER_cmd;
    cmd["JOIN"] = JOIN_cmd;
    cmd["PART"] = PART_cmd;
    cmd["MODE"] = MODE_cmd;
    cmd["TOPIC"] = TOPIC_cmd;
    cmd["KICK"] = KICK_cmd;
    cmd["INVITE"] = INVITE_cmd;
}

int Server::GetCmds(void){
    std::map<std::string, Commands>::iterator it = cmd.find(line[0]);
    if (it != cmd.end()){
        return it->second;
    }
    return UNKNOWN_cmd;
}

void Server::commands_handler(){
    int cmd = GetCmds();
    switch (cmd){
        case 0:
            std::cout<<"PASS"<<std::endl;
            break;
        case 1:
            std::cout<<"NICK"<<std::endl;//try catch throw

            break;
        case 2:
            std::cout<<"USER"<<std::endl;
            break;
        case 3:
            JOIN();
            break;
        case 4:
            std::cout<<"PART"<<std::endl;
            break;
        case 5:
            std::cout<<"MODE"<<std::endl;
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
        default:
            std::cout<<"UNKNOWN"<<std::endl;

    }
    line.clear();
}

void Server::parse_cmd(std::string cmd){

    std::string message = "";
    std::string prefix = "";
    std::string command = "";
    std::string target = "";
    size_t pos = cmd.find(" :");
    if (pos != std::string::npos){
        message = cmd.substr(pos + 2);
        cmd.erase(pos);
    }
    std::stringstream bf(cmd);
    if (cmd[0] == ':'){
        bf>>prefix;
        prefix.erase(0,1);
    }
    bf>>command;
    if (!command.empty()){
        line.push_back(command);
    }
    if (!message.empty()){
        line.push_back(message);
    }
    if (!prefix.empty()){
        line.push_back(prefix);
    }
    while(bf>>target){
        if (!target.empty()){
            line.push_back(target);
        }
    }
    commands_handler();
}
