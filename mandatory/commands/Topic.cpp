/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 21:31:45 by hmoukit           #+#    #+#             */
/*   Updated: 2025/10/23 16:14:20 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/Server.hpp"

void Server::TOPIC(void)
{
	Client &sender = this->_client[this->_currentClient];
	std::vector<std::string> args = this->_line;
	if (args.size() < 2)
	{
		sendReply(sender.getFd(), ERR_NEEDMOREPARAMS(sender.getnick(), "TOPIC"));
		return ;
	}
	std::string channelName = args[1];
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
	if (args.size() == 2)
	{
		if (!chan.hasTopic())
			sendReply(sender.getFd(), RPL_NOTOPIC(sender.getnick(), channelName));
		else
			sendReply(sender.getFd(), RPL_TOPIC(sender.getnick(), channelName, chan.getTopic()));
		return ;
	}
	if (chan.get_t() && !chan.is_Op(sender.getnick()))
	{
		sendReply(sender.getFd(), ERR_CHANOPRIVSNEEDED(sender.getnick(), channelName));
		return ;
	}
	std::string newTopic;
	for (size_t i = 2; i < args.size(); ++i)
	{
		if (i > 2)
			newTopic += " ";
		newTopic += args[i];
	}
	if (newTopic[0] == ':')
		newTopic.erase(0, 1);
	chan.setTopic(newTopic);
	std::string msg = ":" + sender.getPrefix() + " TOPIC " + channelName + " :" + newTopic + "\r\n";
	chan.broadcastReply(msg);
}
