/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 01:55:22 by ychagri           #+#    #+#             */
/*   Updated: 2025/09/05 18:02:51 by ychagri          ###   ########.fr       */
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


const std::string&
Server::parseMode()
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
        std::string time = std::to_string(channel->getTime());
        return  RPL_CHANNELMODEIS(nick,chName , channel->getModes()) +
                RPL_CREATIONTIME(nick, chName, time);
    }

    if (!channel->is_Op(nick))
        return ERR_CHANOPRIVSNEEDED(nick, chName);
    
    int count = 2;
    std::string modes("lko");
    for (size_t i = 0; i < this->_line[3].length(); i++)
    {
        if (modes.find(this->_line[3][i]))
        {
            count++;
            if ((this->_line[3][i] == 'l' || this->_line[3][i] == 'o') 
                && (int)size < count + 1)
                return  ERR_NEEDMOREPARAMS(nick, "MODE");
        }
    }

    char        c = validModeString(this->_line[3]);
    if (c != -1)
        return ERR_UNKNOWNMODE(nick, c);

    return "";
}


void
Server::MODE( void )
{
    
    std::string pareseReply = this->parseMode();
    if (!pareseReply.empty())
        return sendReply(this->_currentClient, pareseReply);

    // if (!channel->is_Member(nick))
    //     return sendReply(fd, ERR_NOTONCHANNEL(nick, chName));
    int         fd = this->_currentClient;
    std::string nick = this->_client[fd].getnick();
    size_t      size = this->_line.size();
    std::string modestring(this->_line[3]);

        

    char        flag = '+';
    std::string validmodes;
    std::string validargs;
    int         count = 2;

    //parse mode 
    
    for (size_t i = 0; i < modestring.length(); i++)
    {

        switch (modestring[i])
        {
            case '+': flag = '+'; break;
            case '-': flag = '-'; break;
            
            case 'i': channel->set_i(flag); break;
            case 't': channel->set_t(flag); break;
            case 'k':
                {

                    count++;
                    if ((int)size >= count + 1)
                    {
                        channel->set_k(flag, this->_line[count]);
                        validmodes += "k";
                        
                    }
                    break;
                }
            case 'o':
                {
                    count++;
                    if ((int)size < count + 1)
                            sendReply(fd, ERR_NEEDMOREPARAMS(nick, "MODE " + flag + "o"));        
                     else
                     {
                        Client  *op = this->userExist(this->_line[count]);
                        if (op)
                            if (!channel->set_o(flag, *op))
                                sendReply(fd, ERR_USERNOTINCHANNEL(nick,  this->_line[count], chName));
                         else
                                sendReply(fd, ERR_NOSUCHNICK(nick, this->_line[count]));
                    }
                    break;                 
                }
            case 'l':
                {
                    count++;
                    if ((int)size < count + 1)
                            sendReply(fd, ERR_NEEDMOREPARAMS(nick, "MODE " + flag + "l"));
                    else
                        channel->set_l(flag, this->_line[count]);
                }
                break;
        
            default:
        
        }
        
    }
            

}