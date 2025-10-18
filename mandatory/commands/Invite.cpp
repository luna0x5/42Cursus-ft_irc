/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 21:31:23 by hmoukit           #+#    #+#             */
/*   Updated: 2025/10/18 16:36:10 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/Server.hpp"

void Server::INVITE(void)
{
	Client &sender = this->_client[this->_currentClient];
	std::vector<std::string> args = this->_line;
	if (args.size() < 3)
	{
		sendReply(sender.getFd(), ERR_NEEDMOREPARAMS(sender.getnick(), "INVITE"));
		return ;
	}
	std::string targetNick = args[1];
	std::string channelName = args[2];
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
	if (chan.get_i() && !chan.is_Op(sender.getnick()))
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
    if (chan.is_Member(targetNick))
    {
		sendReply(sender.getFd(), ERR_USERONCHANNEl(targetNick, channelName));
        return ;
    }
	sendReply(sender.getFd(), RPL_INVITING(sender.getnick(), targetNick, channelName));
	std::stringstream inviteMsg;
    inviteMsg << ":" << sender.getnick() << " INVITE " << targetNick
              << " :" << channelName << "\r\n";
    sendReply(targetClient->getFd(), inviteMsg.str());
	chan.addInvite(targetNick);
}

