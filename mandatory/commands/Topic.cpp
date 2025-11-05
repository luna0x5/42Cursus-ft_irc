/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 21:31:45 by hmoukit           #+#    #+#             */
/*   Updated: 2025/11/05 12:14:04 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/Server.hpp"

void Server::TOPIC(void)
{
	Client &sender = this->_client[this->_currentClient];
	std::vector<std::string> args = this->_line;
	if (args.size() < 2)
	{
		std::cerr<<"sent => ERR_NEEDMOREPARAMS."<<std::endl;
		sendReply(sender.getFd(), ERR_NEEDMOREPARAMS(sender.getnick(), "TOPIC"));
		return ;
	}
	std::string channelName = args[1];
	if (!IsChannelExist(channelName))
	{
		std::cerr<<"sent => ERR_NOSUCHCHANNEL."<<std::endl;
		sendReply(sender.getFd(), ERR_NOSUCHCHANNEL(sender.getnick(), channelName));
		return ;
	}
	Channel &chan = this->_channel[channelName];
	if (!chan.is_Member(sender.getnick()))
	{
		std::cerr<<"sent => ERR_NOTONCHANNEL."<<std::endl;
		sendReply(sender.getFd(), ERR_NOTONCHANNEL(sender.getnick(), channelName));
		return ;
	}
	if (args.size() == 2)
	{
		if (!chan.hasTopic())
		{
			std::cerr<<"sent => RPL_NOTOPIC."<<std::endl;
			sendReply(sender.getFd(), RPL_NOTOPIC(channelName));
		}
		else
		{
			std::cerr<<"sent => RPL_TOPIC."<<std::endl;
			sendReply(sender.getFd(), RPL_TOPIC(channelName, chan.getTopic()));
		}
		return ;
	}
	if (chan.get_t() && !chan.is_Op(sender.get_fd()))
	{
		std::cerr<<"sent => ERR_CHANOPRIVSNEEDED."<<std::endl;
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
