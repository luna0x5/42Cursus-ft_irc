/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 21:31:29 by hmoukit           #+#    #+#             */
/*   Updated: 2025/10/18 16:36:04 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/Server.hpp"

void Server::KICK(void)
{
	Client &sender = this->_client[this->_currentClient];
	std::vector<std::string> args = this->_line;
	if (args.size() < 3)
	{
		sendReply(sender.getFd(), ERR_NEEDMOREPARAMS(sender.getnick(), "KICK"));
		return ;
	}
	std::string channelName = args[1];
	std::string targetNick = args[2];
	if (!IsChannelExist(channelName))
	{
		sendReply(sender.getFd(), ERR_NOSUCHCHANNEL(sender.getnick(), channelName));
		return ;
	}
	Channel &chan = this->_channel[channelName];
	if (!chan.is_Member(sender.getnick()))
	{
		sendReply(sender.getFd(), ERR_NOTONCHANNEL(sender.getnick(), channelName));
		return ;		
	}
	if (!chan.is_Op(sender.getnick()))
	{
		sendReply(sender.getFd(), ERR_CHANOPRIVSNEEDED(sender.getnick(), channelName));
		return ;
	}
	Client* targetClient = userExist(targetNick);
    if (!targetClient)
    {
		sendReply(sender.getFd(), ERR_NOSUCHNICK(sender.getnick(), targetNick));
        return ;
    }
	if (!chan.is_Member(targetClient->getnick()))
	{
		sendReply(sender.getFd(), ERR_NOTONCHANNEL(sender.getnick(), channelName));
		return ;
	}
	std::string comment;
	if (args.size() > 3)
	{
		for (size_t i = 3; i < args.size(); ++i)
		{
			if (i > 3)
				comment += " ";
			comment += args[i];
		}
		if (!comment.empty() && comment[0] == ':')
			comment.erase(0, 1);
	}
	std::string msg = ":" + sender.getPrefix() + " KICK " + channelName + " " + targetNick;
	if (!comment.empty())
		msg += " :" + comment;
	msg += "\r\n";
	chan.removeMember(targetNick);
	chan.broadcastReply(msg);
}

