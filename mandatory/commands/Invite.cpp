/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuury <yuury@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 21:31:23 by hmoukit           #+#    #+#             */
/*   Updated: 2025/11/05 14:30:40 by yuury            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/Server.hpp"

void Server::INVITE(void)
{
	Client &sender = this->_client[this->_currentClient];
	std::vector<std::string> args = this->_line;
	if (args.size() < 3)
	{
		std::cerr<<"sent => ERR_NEEDMOREPARAMS."<<std::endl;
		sendReply(sender.getFd(), ERR_NEEDMOREPARAMS(sender.getnick(), "INVITE"));
		return ;
	}
	std::string targetNick = args[1];
	std::string channelName = args[2];
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
	if (chan.is_inviteOnly() && !chan.is_Op(sender.get_fd()))
	{
		std::cerr<<"sent => ERR_CHANOPRIVSNEEDED."<<std::endl;
		sendReply(sender.getFd(), ERR_CHANOPRIVSNEEDED(sender.getnick(), channelName));
		return ;
	}
	Client* targetClient = userExist(targetNick);
    if (!targetClient)
    {
		std::cerr<<"sent => ERR_NOSUCHNICK."<<std::endl;
		sendReply(sender.getFd(), ERR_NOSUCHNICK(sender.getnick(), targetNick));
        return ;
    }
    if (chan.is_Member(targetNick))
    {
		std::cerr<<"sent => ERR_USERONCHANNEl."<<std::endl;
		sendReply(sender.getFd(), ERR_USERONCHANNEl(targetNick, channelName));
        return ;
    }
	std::cerr<<"sent => RPL_INVITING."<<std::endl;
	sendReply(sender.getFd(), RPL_INVITING(sender.getnick(), targetNick, channelName));
	std::stringstream inviteMsg;
    inviteMsg << ":" << sender.getnick() << " INVITE " << targetNick
              << " :" << channelName << "\r\n";
    sendReply(targetClient->getFd(), inviteMsg.str());
	chan.addInvite(targetNick);
}

