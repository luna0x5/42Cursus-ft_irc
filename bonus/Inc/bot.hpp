#ifndef __BOT__HPP
#define __BOT__HPP

#include "../bot/botClient.hpp"

#define DEFAULT_NICK "BOTIFY"
#define DEFAULT_PASSWORD "password"


#define LOCALHOST "127.0.0.1"
#define PORT 8080

#define RESET   "\033[0m"
#define RED     "\033[31m"    
#define GREEN   "\033[32m"    
#define MAGENTA "\033[35m" 

#define ERR_NEEDMOREPARAMS  461 
#define ERR_NOTREGISTERED   451 
#define RPL_WELCOME         001
#define ERR_ERRONEUSNICKNAME 432 
#define ERR_NICKNAMEINUSE   433
#define ERR_PASSWDMISMATCH         464 

#define ERROR(err) (err == ERR_PASSWDMISMATCH || err == ERR_NICKNAMEINUSE || err == ERR_ERRONEUSNICKNAME || err == ERR_NOTREGISTERED || err == ERR_NEEDMOREPARAMS)


#define LOG(msg) std::cout << GREEN << msg << RESET << std::endl;
#define ELOG(msg) std::cerr << RED << msg << RESET << std::endl;
#define WLOG(msg) std::clog << MAGENTA << msg << RESET << std::endl;

std::string receiveMessage(int socketFd);
void sendMessage(int socketFd, const std::string& message);
std::string trim(const std::string& s) ;
std::vector<std::string> split(std::string &line, char del);

// #define HELP "/listcommands    => Shows all commands available\r\n
//              PASS <password>                => Set connection password"))
//             "NICK <nickname>                => Set or change nickname"))
//             "USER <user> 0 * :<realname>    => Register username and real name"))
//             "JOIN <chan> [key]              => Join or create a channel"))
//             "MODE <chan> [modes]            => View or change channel modes")) 
//             "TOPIC <chan> [topic]           => View or set topic"))
//             "KICK <chan> <nick>             => Kick a user"))
//             "PRIVMSG <target> :<msg>        => Send a private message"))

//                 // Mode options (indented under MODE)
//                             "    +i   => Invite-only channel"))
//                             "    +t   => Only operators may set topic"))
//                             "    +k   => Channel key (password)"))
//                             "    +l   => User limit"))
//                             "    +o   => Give/take channel operator privileges"))







#endif