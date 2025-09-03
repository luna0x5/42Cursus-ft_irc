/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 01:55:22 by ychagri           #+#    #+#             */
/*   Updated: 2025/09/03 14:49:24 by ychagri          ###   ########.fr       */
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



void
Server::MODE( void )
{
    std::string nick = this->_client[this->_currentClient].getnick();
    size_t  size = this->_line.size();
    
    if ( size < 2)
        return (this->sendReply(std::string(ERR_NEEDMOREPARAMS(nick, "MODE"))));

    Channel     *channel = channelExist(this->_line[1]);
    if (!channel)
        return sendReply(ERR_NOSUCHCHANNEL(nick, this->_line[1]));
    
    std::string chName = channel->GetName();
    if (size == 2)
    {
        sendReply(std::string(RPL_CHANNELMODEIS(nick,chName , channel->getModes())));
        std::string time = std::to_string(channel->getTime());
        sendReply(std::string(RPL_CREATIONTIME(nick, chName, time)));
        return;
    }

    if (!channel->is_Member(nick))
        return sendReply(ERR_NOTONCHANNEL(nick, chName));

    int         count = 2;
    bool        op = channel->is_Op(nick);
    std::string modestring(this->_line[3]);
    char        flag = '+';
    
    
    for (size_t i = 0; i < modestring.length(); i++)
    {
        if (validModeString(modestring[i]) && !op)
            sendReply(ERR_CHANOPRIVSNEEDED(nick, chName));
        
        else
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
                        if ((int)this->_line.size() < count + 1)
                            sendReply(ERR_NEEDMOREPARAMS(nick, "MODE " + flag + "k"));
                        else
                            channel->set_k(flag, this->_line[count]);
                        break;
                    }
                case 'o':
                    {
                        count++;
                        if ((int)this->_line.size() < count + 1)
                                sendReply(ERR_NEEDMOREPARAMS(nick, "MODE " + flag + "o"));        
                         else
                         {
                            Client  *op = this->userExist(this->_line[count]);
                            if (op)
                                if (!channel->set_o(flag, *op))
                                    sendReply(ERR_USERNOTINCHANNEL(nick,  this->_line[count], chName));
                             else
                                    sendReply(ERR_NOSUCHNICK(nick, this->_line[count]));
                        }
                        break;                 
                    }
                case 'l':
                    {
                        count++;
                        if ((int)this->_line.size() < count + 1)
                                sendReply(ERR_NEEDMOREPARAMS(nick, "MODE " + flag + "l"));
                        else
                            channel->set_l(flag, this->_line[count]);
                    }
                    break;
            
                default:
                    sendReply(ERR_UNKNOWNMODE(nick, modestring[i]));
            
            }
        }
        
    }
            

}