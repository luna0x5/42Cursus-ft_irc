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
#include <cstring>
#include <map>
#include "Client.hpp"
#include <fcntl.h>
#include <sstream>

class Server {
    private:
        int port;
        std::string password;
        int Socket_fd;
        std::map<int, Client> client;
        // std::vector<Channel*> Channels;
        std::vector<pollfd> poll_fds;
        std::vector<std::string> line;

    public:
        Server(int port , std::string password);
        ~Server();
        int start(void);
        int server_socket(void);
        int running_server(int Socket_fd);
        void handle_new_connections(int Socket_fd);
        void handle_client_data(int fd);
        void parse_cmd(std::string cmd);
        void commands_handler(void);
};

#endif
