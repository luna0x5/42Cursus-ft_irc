#include "Server.hpp"

Server::Server(uint port , std::string password): _port(port), _password(password)
{
    initCmds();
}

Server::~Server()
{
    //destroy all pollfd
}

int 
Server::server_socket()
{
    int err;

    this->_Socket_fd = socket(AF_INET, SOCK_STREAM, 0);// setting server socket with tcp connection and ipv4 
    checkErr(this->_Socket_fd , -1, "Error: Failed to create server socket!");

    int flag = fcntl(this->_Socket_fd, F_GETFL, 0);// get the socket flags to append other flags after without affecting them
    checkErr(flag, -1, "Error: Failed to get server socket status flag!");

    err = fcntl(this->_Socket_fd, F_SETFL, flag | O_NONBLOCK);// setting the socket to non blocking for concurrency
    checkErr(err, -1, "Error: Failed to set socket flag!");

    int opt = 1;
    err = setsockopt(this->_Socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));// Allowing multiple sockets to bind to the same address and port
    checkErr(err, -1, "Error: Failed to set socket option!");

    sockaddr_in serverAdress;// ipv4 socket address
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_port = htons(this->_port);// converting port to network byte order 
    serverAdress.sin_addr.s_addr = htonl(INADDR_ANY);// inaddr to listen for all connections

    err = bind(_Socket_fd, (struct sockaddr *)&serverAdress, sizeof(serverAdress));// naming the socket
    checkErr(err, -1, "Error: Failed to bind!");
    
    err = listen(_Socket_fd, 15);// marking the socket as passive (tcp)
    checkErr(err, -1, "Error: Failed to listen!");
  
    // preparing listening socket to be monitored by poll for new incoming connections
    pollfd listen_fd;
    listen_fd.fd = this->_Socket_fd;
    listen_fd.events = POLLIN;
    this-> _poll_fds.push_back(listen_fd);

    return(this->_Socket_fd);
}

int Server::running_server(int Socket_fd){
    while(true){
        int monitor = poll(poll_fds.data(), poll_fds.size(), -1);
        if (monitor < 0){
            throw std::runtime_error("Error : Failed poll");
        }
        for (size_t i=0 ; i < poll_fds.size() ; i++){
            if (poll_fds[i].revents & POLLIN){
                if (poll_fds[i].fd == Socket_fd){
                    handle_new_connections(_Socket_fd);
                }
                else{
                    char buffer[1048];
                    memset(buffer, 0, sizeof(buffer));
                    int bytes = recv(poll_fds[i].fd, buffer, sizeof(buffer), 0);
                    if (bytes <= 0){
                        close(poll_fds[i].fd);
                        std::cout<<"client : "<<poll_fds[i].fd<<" deconnecte"<<std::endl;
                        client.erase(poll_fds[i].fd);
                        poll_fds.erase(poll_fds.begin() + i);
                        i--;
                    }
                    else{
                        buffer[bytes] = '\0';
                        client[poll_fds[i].fd].AddBuffer(buffer);
                        client[poll_fds[i].fd].extract_cmds();
                        handle_client_data(poll_fds[i].fd);
                    }
                }
            }
        }
    }
}

int Server::start(){
    int socket_fd;
    try{
        socket_fd = server_socket();
    }
    catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
    try{
        if (running_server(socket_fd) < 0){
            return(-1);
        }
    }
    catch (const std::exception& e){
        std::cerr <<e.what()<<std::endl;
    }
    return (1);
}


void
Server::checkErr(const int res, const int err, const char *msg)
{
    if (res == err)
        throw std::runtime_error(msg);
    return ;
}


//signals :
