/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericalReplies.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 01:17:18 by ychagri           #+#    #+#             */
/*   Updated: 2025/09/08 12:11:20 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

#define SERVERNAME                      "localhost"

#define ERR_NEEDMOREPARAMS(clnt, cmd)               ":"  SERVERNAME " 461 " + clnt + " " + cmd + " :Not enough parameters\r\n"
#define RPL_CHANNELMODEIS(clnt, chnl, mod)          ":"  SERVERNAME " 324 " + clnt + " " + chnl + " " + mod + "\r\n"
#define RPL_CREATIONTIME(clnt,chnl,t)               ":"  SERVERNAME " 329 " + clnt + " " + chnl + " " + t + "\r\n"
#define ERR_NOSUCHCHANNEL(clnt, chnl)               ":"  SERVERNAME " 403 " + clnt + " " + chnl + " :No such channel\r\n"
#define ERR_UNKNOWNMODE(clnt, mod)                  ":"  SERVERNAME " 472 " + clnt + " " + mod + " :is an unknown mode char to me\r\n"
#define ERR_CHANOPRIVSNEEDED(clnt, chnl)            ":"  SERVERNAME " 482 " + clnt + " " + chnl + " :You're not a channel operator\r\n"
#define ERR_NOTONCHANNEL(clnt, chnl)                ":"  SERVERNAME " 442 " + clnt + " " + chnl + " :You're not on that channel\r\n"
#define ERR_NOSUCHNICK(clnt,nkname)                 ":"  SERVERNAME " 401 " + clnt + " " + nkname + " :No such nick\r\n"
#define ERR_USERNOTINCHANNEL(clnt, nkname, chnl)    ":"  SERVERNAME " 441 " + clnt + " " + nkname + " " +chnl + " :They aren't on that channel\r\n" 

char    validModeString( char mode );

// void sendServerRpl(int const client_fd, std::string client_buffer); //This function takes a client file descriptor and a formatted message buffer, then sends the message to the appropriate client.