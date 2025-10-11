#include "../server/Server.hpp"

Channel*
Server::channelExist( const std::string &name )
{
    ch_it  itt = this->_channel.find(name);

    if (itt != this->_channel.end())
        return &itt->second;
    return NULL;
}

Client*
Server::userExist( const std::string &name )
{
    cl_it  itt = this->_client.begin();

    for (; itt != this->_client.end(); itt++)
        if (itt->second.getnick() == name)
            return &itt->second;
    return NULL;
}


const std::string
Server::parseMode( void )
{
    int         fd      = this->_currentClient;
    std::string nick    = this->_client[fd].getnick();
    size_t      size    = this->_line.size();

    if ( size < 2)
        return ERR_NEEDMOREPARAMS(nick, "MODE");
    
    Channel     *channel = channelExist(this->_line[1]);
    if (!channel)
        return ERR_NOSUCHCHANNEL(nick, this->_line[1]);
    
    std::string chName = channel->GetName();
    if (size == 2)
    {
        std::string time = to_string<time_t>(channel->getTime());
        return  RPL_CHANNELMODEIS(nick,chName , channel->getModes()) +
                RPL_CREATIONTIME(nick, chName, time);
    }

    int count = 2;
    std::string modes("lko");
    char        flag = '+';

    for (size_t i = 0; i < this->_line[3].length(); i++)
    {
        if (modes.find(this->_line[3][i]))
        {
            count++;
            if (((this->_line[3][i] == 'l' && flag == '+')|| this->_line[3][i] == 'o') 
                && (int)size < count + 1)
                return  ERR_NEEDMOREPARAMS(nick, "MODE");
        }
        else if (validModeString(this->_line[3][i]) == -1)
            return ERR_UNKNOWNMODE(nick, this->_line[3][i]);
        else if (this->_line[3][i] == '+' || this->_line[3][i] == '-')
            flag = this->_line[3][i];
    }

    if (!channel->is_Op(nick))
        return ERR_CHANOPRIVSNEEDED(nick, chName);

    return "";
}


void
Server::MODE( void )
{
    
    std::string pareseReply = this->parseMode();
    if (!pareseReply.empty())
        return sendReply(this->_currentClient, pareseReply);

    int         fd = this->_currentClient;
    std::string nick = this->_client[fd].getnick();
    size_t      size = this->_line.size();
    std::string modestring(this->_line[3]);
    Channel     *channel = channelExist(this->_line[1]);
    char        flag = '+';
    int         count = 2;
    bool        f = false;
    
    for (size_t i = 0; i < modestring.length(); i++)
    {
        while (modestring[i] && (modestring[i] == '+' || modestring[i] == '-'))
        {
            flag = modestring[i];
            i++;
            f = true;
        }
        if (f || i == 0)
            channel->changedModes+= flag;
        switch (modestring[i])
        {
            case 'i': channel->set_i(flag); break;
            case 't': channel->set_t(flag); break;
            case 'k':
            {
                count++;
                if ((int)size >= count + 1)
                    channel->set_k(flag, this->_line[count]);
                break;
            }
            case 'o':
            {
                count++;
                Client  *op = this->userExist(this->_line[count]);
                if (op && !channel->set_o(flag, *op))
                        sendReply(fd, ERR_USERNOTINCHANNEL(nick,  this->_line[count], channel->GetName()));
                 else if (!op)
                        sendReply(fd, ERR_NOSUCHNICK(nick, this->_line[count]));
                break;                 
            }
            case 'l':
            {
                count++;
                channel->set_l(flag, this->_line[count]);
                break;
            }
        
        }
        
    }

    channel->broadcastReply(RPL_MODE(channel->GetName(), channel->changedModes, channel->args));

}
