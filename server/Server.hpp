#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <vector>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>

class Server {
    private:
        int port;
        std::string password;
        int Socket_fd;
        // std::vector<Client*> clients;
        // std::vector<Channel*> Channels;
        std::vector<pollfd*> poll_fds; 

    public:
        void start();
        int server_socket();
        void running_server(int fd);
        void handle_new_connections();
        void handle_client_data();
};

#endif