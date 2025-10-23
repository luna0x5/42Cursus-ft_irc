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
#include <stdexcept>
#include <algorithm>

#include "numericalReplies.hpp"
// #include "Channel.hpp"
class Channel;

enum Commands {
    PASS_cmd,
    NICK_cmd,
    USER_cmd,
    JOIN_cmd,
    MODE_cmd,
    TOPIC_cmd,
    KICK_cmd,
    INVITE_cmd,
    BOT_CMD,
	PRIVMSG_cmd,
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
            std::map<std::string, Channel>  _channel;
            std::vector<pollfd>             _poll_fds;
            std::vector<std::string>        _line;
            std::map<std::string, Commands> _cmd;//TODO: better add pointer to the command handler instead

            std::string                     _serverName;

            typedef std::map<std::string, Channel>::iterator ch_it;
            typedef std::map<int, Client>::iterator          cl_it;

			bool							checkPriv;

    public:
            Server(uint port , std::string password);
            ~Server();
            void     start(void);
            
            static void        sendReply(int fd,  const std::string& reply);
            static void        Handler(int sig);

    private :

            int         server_socket(void);
            void        running_server(int Socket_fd);

            void        handle_new_connections(int Socket_fd);
            void        handle_client_data(int fd);

            void        parse_cmd(std::string cmd);
            void        commands_handler(void);
            void        initCmds(void);
            int         GetCmds(void);
    
            int         ft_split(std::vector<std::string> *channels, std::string& chan, char delimiter);

            int JoinParse(std::vector<std::string> *channels, std::vector<std::string> *keys);
            void        JOIN(void);

            void        PASS(void);

            void        NICK(void);
            bool        Nickparse(void);
            bool        firstChar(void);
            bool        AlreadyInUse(void);
            bool        otherChar(void);

            void        USER(void);

			void		INVITE(void);
			void		KICK(void);
			void		PRIVMSG(void);
			void		TOPIC(void);

            void                checkErr(const int res, const int err, const char *msg);
            Channel*            channelExist( const std::string &name );
            Client*             userExist( const std::string &nick);
            const std::string   parseMode( void );
            void                MODE( void );

            const std::string   botParser( void );
            void                help( void );
            void                helpRpl(const std::string &option, const std::string reply[], int size);
            void                whois( int fd, const std::string &nick);
            void                listcmds( void );
            void                listusers(int fd, const std::string &nick);
            void                BOT( void );

            void        cleaner(void);
            void        OneClean(void);
            bool        findit(pollfd p);

            bool        Already_in_channel(Channel &chan, const std::string &nick);

			int         IsChannelExist(std::string ChanName);

			bool getChekPriv(void);
			void setCheckPriv(bool check);
        //     bool        Invite_only(Channel &chan);
        //     void        sendReply(const reply code, const std::string cmdName);

};

#include "Channel.hpp"

#endif
