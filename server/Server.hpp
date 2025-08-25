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
#include "../client/Client.hpp"
#include <fcntl.h>
#include <sstream>
#include <stdexcept>
#include "../channel/Channel.hpp"
#include <algorithm>

enum Commands {
    PASS_cmd,
    NICK_cmd,
    USER_cmd,
    JOIN_cmd,
    PART_cmd,
    MODE_cmd,
    TOPIC_cmd,
    KICK_cmd,
    INVITE_cmd,
    UNKNOWN_cmd
};


class Server
{
    private:

            uint                            _port;
            std::string                     _password;
            int                             _Socket_fd;
            std::map<int, Client>           _client;
            int                             _currentClient;
            std::vector<Channel>            _channel;
            std::vector<pollfd>             _poll_fds;
            std::vector<std::string>        _line;
            std::map<std::string, Commands> _cmd;//TODO: better add pointer to the command handler instead

    public:

            Server(uint port , std::string password);
            ~Server();
            void     start(void);
    
    private :

            int         server_socket(void);
            void        running_server(int Socket_fd);

            void        handle_new_connections(int Socket_fd);
            void        handle_client_data(int fd);

            void        parse_cmd(std::string cmd);
            void        commands_handler(void);
            void        initCmds(void);
            int         GetCmds(void);
    
            int         IsChannelExist(std::string ChanName);
            int         split(std::vector<std::string> *channels, std::string& chan, char delimiter);
            void        checkErr(const int res, const int err, const char *msg);

            int         JoinParse(std::vector<std::string> *channels, std::vector<std::string> *keys);
            void        JOIN(void);

            void        PASS(void);

            void        NICK(void);
            bool        Nickparse(void);
            bool        firstChar(void);
            bool        AlreadyInUse(void);
            bool        otherChar(void);

            void        USER(void);

            void        Sender(std::string num);

};

#endif
