#include "Server.hpp"

void Server::handle_new_connections(int Socket_fd){
    sockaddr_in clientAdress;
    socklen_t len = sizeof(clientAdress);
    int new_socket = accept(Socket_fd, (struct sockaddr *) &clientAdress, &len);
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

void Server::commands_handler(){
    if (line[0] == "JOIN"){
        std::cout<<"join"<<std::endl;
    }
    else if (line[0] == "NICK"){
        std::cout<<"nick"<<std::endl;
    }
    else if (line[0] == "PRIVMSG"){
        std::cout<<"privmsg"<<std::endl;
    }
    else if (line[0] == "PONG"){
        std::cout<<"pong"<<std::endl;
    }
    else if (line[0] == "PING"){
        std::cout<<"ping"<<std::endl;
    }
    else{
        std::cout<<"Unknown command: "<<line[0]<<std::endl;
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
    bf>>target;
    if (!command.empty()){
        line.push_back(command);
    }
    if (!target.empty()){
        line.push_back(target);
    }
    if (!message.empty()){
        line.push_back(message);
    }
    if (!prefix.empty()){
        line.push_back(prefix);
    }

    for(size_t i=0; i < line.size(); i++){
        std::cout<< i << " : "<< line[i]<<std::endl;
    }
    commands_handler();
}
