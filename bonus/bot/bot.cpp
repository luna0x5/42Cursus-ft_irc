#include "Server.hpp"


const std::string
Server::botParser( void )
{
    std::string nick = this->_client[this->_currentClient].getnick();
    size_t  size = this->_line.size(); 
    std::string opt = this->_line[1];
    
    if (size < 2)
        return ERR_NEEDMOREPARAMS(nick, "/BOT");
    else if ((opt == "-whois" ||  opt == "-listusers") && size <= 2)
        return ERR_NEEDMOREPARAMS(nick, "/BOT " + opt);
    if (opt == "help" || opt == "-listcmds" || opt == "-whois" ||  opt == "-listusers")
        return opt;
    else
        return ERR_HELPNOTFOUND(nick, opt);
}

void
Server::helpRpl(const std::string &option, const std::string reply[], int size)
{

    int         fd = this->_currentClient;
    std::string nick = this->_client[fd].getnick();

    sendReply(fd, RPL_HELPSTART(nick, option));
    for(int i = 0; i < size; i++)
        sendReply(fd, RPL_HELPTXT(nick, option, reply[i]));
    sendReply(fd, RPL_ENDOFHELP(nick, option));
}

void
Server::help( void )
{
    std::string reply[] = {RPL_WHOIS, RPL_LISTUSERS, RPL_LISTCMDS};
    helpRpl("help",reply, 3);
} 

void
Server::whois(int fd, const std::string& nick)
{
    Client  *client = userExist(this->_line[2]);
    if (!client)
        return sendReply (fd, ERR_NOSUCHNICK(nick, this->_line[2]));

    std::string reply[] =   {   W_USERNAME(client->GetUsername()),
                                W_NICKNAME(client->getnick()),
                                W_REALNAME(client->getrealname())
                            };
    
    helpRpl( "-whois", reply, 3);
}

void
Server::listcmds( void )
{
    std::string reply[] = {
                "--------- Bonus commands -----------",
                RPL_CMD_HELP,
                RPL_WHOIS,
                RPL_LISTUSERS,
                RPL_LISTCMDS,
                "--------- mandatory commands -----------",
                RPL_CMD_PASS,
                RPL_CMD_NICK,
                RPL_CMD_USER,
                RPL_CMD_JOIN,
                RPL_CMD_PART,
                RPL_CMD_MODE,
                RPL_MODE_I,
                RPL_MODE_T,
                RPL_MODE_K,
                RPL_MODE_L,
                RPL_MODE_O,
                RPL_CMD_TOPIC,
                RPL_CMD_KICK,
                RPL_CMD_PRIVMSG,
                };
    helpRpl( "-listcmds", reply, 20);
}


void
Server::listusers(int fd, const std::string &nick)
{
    Channel *channel = this->channelExist(this->_line[2]);

    if (!channel)
        return sendReply(fd, ERR_NOSUCHCHANNEL(nick, this->_line[2]));

    std::map<std::string, Client>  members = channel->GetMembers();
    std::vector<std::string> names;
    for (std::map<std::string, Client>::iterator it = members.begin(); it != members.end(); ++it)
        names.push_back(it->first);

    helpRpl( "-listusers", &names[0], channel->getMembersCount());

}

void
Server::BOT()
{
    int         fd = this->_currentClient;
    std::string nick = this->_client[fd].getnick();
    std::string option = this->botParser();

    if (option == "help")
        return this->help();
    else if (option == "-whois")
        return this->whois(fd, nick);
    else if (option == "-listcmds")
        return this->listcmds();
    else if (option == "-listusers")
        return this->listusers(fd, nick);
    else
        return sendReply(fd, option);
}