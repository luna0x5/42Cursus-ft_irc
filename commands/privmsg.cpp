/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 02:47:29 by hmoukit           #+#    #+#             */
/*   Updated: 2025/09/14 17:17:29 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/Channel.hpp"
#include "../Inc/Client.hpp"
#include "../Inc/numericalReplies.hpp"
#include "../Inc/Server.hpp"

void Server::PRIVMSG(Server &server, Client &client, const std::vector<std::string> &args)
{
    (void)server;
    if (args.size() < 3)
    {
        sendReply(client.getFd(), "461" + client.getnick() + " PRIVMSG: NOT ENOUGH PARAMS");
        return ;
    }
}
