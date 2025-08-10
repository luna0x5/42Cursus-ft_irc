#include "Server.hpp"

Server::Server(uint _port , std::string _password): port(_port), password(_password){
    initCmds();
}

Server::~Server(){
    //destroy all pollfd
}

int Server::server_socket(){
    Socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    int flag = fcntl(Socket_fd, F_GETFL, 0);
    fcntl(Socket_fd, F_SETFL, flag | O_NONBLOCK);

    int opt = 1;
    if (setsockopt(Socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
        throw std::runtime_error("Error : Failed to set options");
    }

    sockaddr_in serverAdress;
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_port = htons(port);
    serverAdress.sin_addr.s_addr = INADDR_ANY;

    if (bind(Socket_fd, (struct sockaddr *)&serverAdress, sizeof(serverAdress)) < 0){
        throw std::runtime_error("Error : Failed to bind");
    }

    if (listen(Socket_fd, 15) == -1){
        throw std::runtime_error("Error : Failed to listen");
    }
    pollfd listen_fd;
    listen_fd.fd = Socket_fd;
    listen_fd.events = POLLIN;
    poll_fds.push_back(listen_fd);

    return(Socket_fd);
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
                    handle_new_connections(Socket_fd);
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

//signals :
