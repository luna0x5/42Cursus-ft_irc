/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 02:47:29 by hmoukit           #+#    #+#             */
/*   Updated: 2025/10/26 16:50:29 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/Server.hpp"

void Server::PRIVMSG(void)
{
	Client &sender = this->_client[this->_currentClient];
	std::vector<std::string> args = this->_line;
	if (args.size() < 2)
	{
		sendReply(sender.getFd(), ERR_NEEDMOREPARAMS(sender.getnick(), "PRIVMSG"));
		return ;
	}
	std::string targets;
	std::string message;
	if (getChekPriv())
	{
		setCheckPriv(false);
		if (args.size() > 2)
		{
			message = args[1].substr(1);
			targets = args[2];
		}
		else
		{
			sendReply(sender.getFd(), ERR_NORECIPIENT(sender.getnick(), "PRIVMSG"));
			return;
		}
	}

	else
	{
		targets = args[1];
		for(size_t i = 2; i < args.size(); ++i)
		{
			if (i == 2 && args[i][0] == ':')
			message += args[i].substr(1);
			else
			message += " " + args[i];
		}
	}
	if (message.empty())
	{
		sendReply(sender.getFd(), ERR_NOTEXTTOSEND(sender.getnick(), "PRIVMSG"));
		return ;
	}
	std::stringstream ss(targets);
	std::string target;
	while (std::getline(ss, target, ','))
	{
		if (target.empty())
			continue;
		if (target[0] == '#')
		{
			if (this->_channel.find(target) == this->_channel.end())
			{
				sendReply(sender.getFd(), ERR_NOSUCHCHANNEL(sender.getnick(), "PRIVMSG"));
				continue;
			}
			Channel &chan = this->_channel[target];
			if (!chan.is_Member(sender.getnick()))
			{
				sendReply(sender.getFd(), ERR_CANNOTSENDTOCHAN(chan.GetName()));
				continue;
			}
			std::string msg = ":" + sender.getPrefix() + " PRIVMSG " + target + " :" + message + "\r\n";
			chan.broadcastReply(msg);
		}
        else
        {
            Client *receiver = userExist(target);
            if (!receiver)
            {
                sendReply(sender.getFd(), ERR_NOSUCHNICK(sender.getnick(), target));
                continue;
            }

            std::string msg = ":" + sender.getPrefix() + " PRIVMSG " + target + " :" + message + "\r\n";
            send(receiver->getFd(), msg.c_str(), msg.length(), 0);
        }
	}
}
