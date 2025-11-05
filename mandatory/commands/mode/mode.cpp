/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuury <yuury@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 01:55:22 by ychagri           #+#    #+#             */
/*   Updated: 2025/11/05 14:49:01 by yuury            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.hpp"

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
        return std::cerr << "sent => ERR_NEEDMOREPARAMS." << std::endl, ERR_NEEDMOREPARAMS(nick, "MODE");

    Channel     *channel = channelExist(this->_line[1]);
    if (!channel)
        return std::cerr<<"sent => ERR_NOSUCHCHANNEL."<<std::endl, ERR_NOSUCHCHANNEL(nick, this->_line[1]);
    
    std::string chName = channel->GetName();
    if (size == 2)
    {
        std::string time = to_string<time_t>(channel->getTime());
        std::cerr<<"sent => RPL_CHANNELMODEIS."<<std::endl;
        std::cerr<<"sent => RPL_CREATIONTIME."<<std::endl;
        return  RPL_CHANNELMODEIS(nick,chName , channel->getModes()) +
                RPL_CREATIONTIME(nick, chName, time);
    }

    int count = 2;
    std::string modes("lko");
    char        flag = '+';

    for (size_t i = 0; i < this->_line[2].length(); i++)
    {
        if (modes.find(this->_line[2][i]) != std::string::npos)
        {
            count++;
            if (((this->_line[2][i] == 'l' && flag == '+')|| this->_line[2][i] == 'o') 
                && (int)size < count + 1)
                return  std::cerr<<"sent => ERR_NEEDMOREPARAMS."<<std::endl, ERR_NEEDMOREPARAMS(nick, "MODE");
        }
        else if (validModeString(this->_line[2][i]) == -1)
            return std::cerr<<"sent => ERR_UNKNOWNMODE."<<std::endl, ERR_UNKNOWNMODE(nick, this->_line[2][i]);
        else if (this->_line[2][i] == '+' || this->_line[2][i] == '-')
            flag = this->_line[2][i];
    }

    if (channel->is_Op(fd) == false)
        return std::cerr<<"sent => ERR_CHANOPRIVSNEEDED."<<std::endl, ERR_CHANOPRIVSNEEDED(nick, chName);

    return "";
}


void
Server::MODE( void )
{
    int         fd = this->_currentClient;
 
    if (this->_client[fd].getregistered() == false)
        return std::cerr << "sent => ERR_NOTREGISTERED." << std::endl,  sendReply(fd, ERR_NOTREGISTERED(std::string("*")));



    std::string pareseReply = this->parseMode();
    if (!pareseReply.empty())
        return sendReply(this->_currentClient, pareseReply);

        
    std::string nick = this->_client[fd].getnick();
    size_t      size = this->_line.size();
    std::string modestring(this->_line[2]);
    Channel     *channel = channelExist(this->_line[1]);
    char        flag = '+';
    int         count = 2;
    bool        f = false;

    channel->changedModes.clear();
    channel->args.clear();
    
    for (size_t i = 0; i < modestring.length(); i++)
    {
        while (modestring[i] && (modestring[i] == '+' || modestring[i] == '-'))
        {
            flag = modestring[i];
            f = true;
            i++;
        }
        if (i == modestring.length())
            return ;
        if ((f || i == 0) )
        {
            if (channel->changedModes[channel->changedModes.length() - 1] == '-'
                || channel->changedModes[channel->changedModes.length() - 1] == '+')
                    channel->changedModes[channel->changedModes.length() - 1] = 0;
            size_t pos = channel->changedModes.find_last_of("-+");
            if (flag != channel->changedModes[pos])
                channel->changedModes+= flag;
        }
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
                if (op && channel->set_o(flag, op) == false)
                {
                    sendReply(fd, ERR_USERNOTINCHANNEL(nick,  this->_line[count], channel->GetName()));
                    std::cerr<<"sent => ERR_USERNOTINCHANNEL." << std::endl;
                }
                 else if (!op)
                 {
                     sendReply(fd, ERR_NOSUCHNICK(nick, this->_line[count]));
                    std::cerr<<"sent => ERR_NOSUCHNICK." << std::endl;
                 }
                break;                 
            }
            case 'l':
            {
                count++;
                channel->set_l(flag, this->_line[count]);
                break;
            }
        
        }
        f = false;
        
    }
    
    int strsize = channel->changedModes.length();

    for (int i = strsize - 1; i >= 0 && (channel->changedModes[i] == '+' || channel->changedModes[i] == '-') ; i--)
        channel->changedModes.erase(i);

    if (channel->changedModes.empty() == false)
        channel->broadcastReply(RPL_MODE(channel->GetName(), channel->changedModes, channel->args));

}