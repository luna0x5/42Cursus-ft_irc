#include "Server.hpp"
#include "Channel.hpp"

void Server::handle_new_connections(int server_fd)
{
    sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
    if (client_fd < 0) {
        //print error;
        return;
    }

    // Optional: make the client socket non-blocking
    int flags = fcntl(client_fd, F_GETFL, 0);
    fcntl(client_fd, F_SETFL, flags | O_NONBLOCK);

    // Create Client object with proper fd
    Client new_client(client_fd); // make sure Client stores fd in getFd()

    // Store in your client map
    _client[client_fd] = new_client;

    // Add to poll list
    pollfd pfd;
    pfd.fd = client_fd;
    pfd.events = POLLIN;
    _poll_fds.push_back(pfd);

    std::cout << "New client connected: fd " << client_fd << std::endl;
}


// not working for me
// void
// Server::handle_new_connections(int Socket_fd)
// {
//     sockaddr_in clientAdress;
//     socklen_t   len = sizeof(clientAdress);

//     int         new_socket = accept(Socket_fd, (struct sockaddr *) &clientAdress, &len);//accepting the incoming request    
//     checkErr(new_socket, -1, "failed to accept new connection!");
//     std::cout << "client connected" << std::endl;

//     checkErr(fcntl(new_socket, F_SETFL, O_NONBLOCK), -1, "failed to add file flags!");

//     pollfd new_fd;
//     new_fd.fd = new_socket;
//     new_fd.events = POLLIN;
//     this->_poll_fds.push_back(new_fd);
//     this->_client[new_fd.fd] = Client();
// }

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
    this->_cmd["PRIVMSG"] = PRIVMSG_cmd;
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
            std::cout<<"PASS"<<std::endl;
            break;
        case 1:
            NICK();
            std::cout<<"NICK"<<std::endl;
            break;
        case 2:
            USER();
            std::cout<<"USER"<<std::endl;
            break;
        case 3:
            // JOIN();
            std::cout<<"JOIN"<<std::endl;
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
        case 9:
            PRIVMSG(*this, _client[_currentClient], _line); //HERE
            std::cout << "PRIVMSG" << std::endl;
            break;
        default:
            std::cout<<"UNKNOWN"<<std::endl;
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

void Server::Sender(std::string num){
    std::string to_client   = ":localhost " + num + this->_client[this->_currentClient].getnick() + " :Welcome to our server\r\n";
    int         bytes       = send(this->_currentClient, to_client.c_str(), to_client.length(), 0);
    if(bytes < 0){
        std::cerr<<"failed send data "<<std::endl;
    }
}
#include <errno.h> //REMOVE
void
Server::sendReply(int fd, const std::string& reply)
{
    
    int         bytes = send(fd, reply.c_str(), reply.length(), 0);
    std::cout << "fd ==== " << fd << std::endl; //REMOVE
    if (bytes < 0) // this to print the errno
        std::cerr << "Error: Failed send data ! errno: " << errno
                  << " - " << strerror(errno) << std::endl;
    // if(bytes < 0)
    //     std::cerr<<"Error: Failed send data !"<<std::endl;
}
