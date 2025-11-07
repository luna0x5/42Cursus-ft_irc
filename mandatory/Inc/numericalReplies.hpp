/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericalReplies.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 01:17:18 by ychagri           #+#    #+#             */
/*   Updated: 2025/11/07 16:35:23 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

#define SERVERNAME                      (std::string("localhost"))

// Standard errors & replies
#define ERR_NEEDMOREPARAMS(clnt, cmd)            (std::string(":") + SERVERNAME + " 461 " + clnt + " " + cmd + " :Not enough parameters\r\n")
#define RPL_CHANNELMODEIS(clnt, chnl, mod)       (std::string(":") + SERVERNAME + " 324 " + clnt + " " + chnl + " " + mod + "\r\n")
#define RPL_CREATIONTIME(clnt, chnl, t)          (std::string(":") + SERVERNAME + " 329 " + clnt + " " + chnl + " " + t + "\r\n")
#define ERR_NOSUCHCHANNEL(clnt, chnl)            (std::string(":") + SERVERNAME + " 403 " + clnt + " " + chnl + " :No such channel\r\n")
#define ERR_UNKNOWNMODE(clnt, mod)               (std::string(":") + SERVERNAME + " 472 " + clnt + " " + mod + " :is an unknown mode char to me\r\n")
#define ERR_CHANOPRIVSNEEDED(clnt, chnl)         (std::string(":") + SERVERNAME + " 482 " + clnt + " " + chnl + " :You're not a channel operator\r\n")
#define ERR_NOTONCHANNEL(clnt, chnl)             (std::string(":") + SERVERNAME + " 442 " + clnt + " " + chnl + " :You're not on that channel\r\n")
#define ERR_USERONCHANNEL()
#define ERR_NOSUCHNICK(clnt, nkname)             (std::string(":") + SERVERNAME + " 401 " + clnt + " " + nkname + " :No such nick\r\n")
#define ERR_USERNOTINCHANNEL(clnt, nkname, chnl) (std::string(":") + SERVERNAME + " 441 " + clnt + " " + nkname + " " + chnl + " :They aren't on that channel\r\n") 
#define RPL_MODE(nick, chnl, mod, args)          (std::string(":") + nick + "!~" + nick + "@" + SERVERNAME + " MODE "+ chnl + " " + mod + args + "\r\n")
#define ERR_NOTREGISTERED(clnt)                  (std::string(":") + SERVERNAME + " 451 " + clnt + " :You have not registered\r\n")

#define RPL_WELCOME(clnt)                 (std::string(":") + SERVERNAME + " 001 " + clnt + " :Welcome\r\n")
#define RPL_JOIN(clnt, chnl)              (std::string(":") + SERVERNAME + " JOIN " + clnt + " " + chnl + " :has joined a channel\r\n")
#define ERR_BANNEDFROMCHAN(clnt, chnl)    (std::string(":") + SERVERNAME + " 474 " + clnt + " " + chnl + " :Cannot join because you are banned\r\n")
#define ERR_BADCHANNELKEY(clnt, chnl)     (std::string(":") + SERVERNAME + " 475 " + clnt + " " + chnl + " :Incorrect channel key\r\n")
#define ERR_NONICKNAMEGIVEN(clnt)         (std::string(":") + SERVERNAME + " 431 " + clnt + " :No nickname provided\r\n")
#define ERR_ERRONEUSNICKNAME(clnt, nick)  (std::string(":") + SERVERNAME + " 432 " + clnt + " " + nick + " :Erroneous nickname\r\n")
#define ERR_NICKNAMEINUSE(clnt, nick)     (std::string(":") + SERVERNAME + " 433 " + clnt + " " + nick + " :Nickname is already in use\r\n")
#define ERR_ALREADYREGISTERED(clnt)       (std::string(":") + SERVERNAME + " 462 " + clnt + " :You are already registered\r\n")
#define ERR_PASSWDMISMATCH(clnt)          (std::string(":") + SERVERNAME + " 464 " + clnt + " :Incorrect password\r\n")
#define ERR_INVITEONLYCHAN(clnt, chnl)    (std::string(":") + SERVERNAME + " 473 " + clnt + " " + chnl + " :Invite only channel\r\n")
#define ERR_CHANNELISFULL(clnt, chnl)     (std::string(":") + SERVERNAME + " 471 " + clnt + " " + chnl + " :Channel is full\r\n")

#define ERR_NOTEXTTOSEND(clnt, cmd)		  (std::string(":") + SERVERNAME + " 412 " + clnt + " " + cmd + " :No text to send\r\n")
#define ERR_CANNOTSENDTOCHAN(chnl)  	  (std::string(":") + SERVERNAME + " 404 " + chnl + " :Cannot send to channel\r\n")
#define RPL_NOTOPIC(chnl)		      	  (std::string(":") + SERVERNAME + " 331 " + chnl + " :No topic is set\r\n")
#define RPL_TOPIC(chnl, topic)	  		  (std::string(":") + SERVERNAME + " 332 " + chnl + " :" + topic + "\r\n")
#define ERR_USERONCHANNEl(tnick, chnl)	  (std::string(":") + SERVERNAME + " 443 " + tnick + " " + chnl + " :is already on channel\r\n")
#define RPL_INVITING(clnt, tnick, chnl)	  (std::string(":") + SERVERNAME + " 341 " + clnt + " " + tnick + " " + chnl + " :invite\r\n")
#define ERR_NORECIPIENT(clnt, cmd) 		  (std::string(":") + SERVERNAME + " 411 " + clnt + " " + cmd + " :No recipient given\r\n")



char    validModeString( char mode );

template <typename T>
std::string to_string(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}
