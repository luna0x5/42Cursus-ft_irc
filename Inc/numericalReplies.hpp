
// #pragma once

#include <iostream>

#define SERVERNAME                      "localhost"

#define ERR_NEEDMOREPARAMS(clnt, cmd)               ":" SERVERNAME " 461 " + clnt + " " + cmd + " :Not enough parameters\r\n"
#define RPL_CHANNELMODEIS(clnt, chnl, mod)          ":" SERVERNAME " 324 " + clnt + " " + chnl + " " + mod + "\r\n"
#define RPL_CREATIONTIME(clnt,chnl,t)               ":" SERVERNAME " 329 " + clnt + " " + chnl + " " + t + "\r\n"
#define ERR_NOSUCHCHANNEL(clnt, chnl)               ":" SERVERNAME " 403 " + clnt + " " + chnl + " :No such channel\r\n"
#define ERR_UNKNOWNMODE(clnt, mod)                  ":" SERVERNAME " 472 " + clnt + " " + mod + " :is an unknown mode char to me\r\n"
#define ERR_CHANOPRIVSNEEDED(clnt, chnl)            ":" SERVERNAME " 482 " + clnt + " " + chnl + " :You're not a channel operator\r\n"
#define ERR_NOTONCHANNEL(clnt, chnl)                ":" SERVERNAME " 442 " + clnt + " " + chnl + " :You're not on that channel\r\n"
#define ERR_NOSUCHNICK(clnt,nkname)                 ":" SERVERNAME " 401 " + clnt + " " + nkname + " :No such nick\r\n"
#define ERR_USERNOTINCHANNEL(clnt, nkname, chnl)    ":" SERVERNAME " 441 " + clnt + " " + nkname + " " +chnl + " :They aren't on that channel\r\n" 
#define RPL_MODE(chnl, mod, args)                   ":" SERVERNAME " MODE "+ chnl + " " + mod + args + "\r\n"

#define RPL_WELCOME(clnt)                           ":" SERVERNAME " 001 " + clnt + " :Welcome\r\n"
#define RPL_JOIN(clnt, chnl)                        ":" SERVERNAME "  JOIN " + clnt + " " + chnl + " :has joined a channel\r\n"
#define ERR_BANNEDFROMCHAN(clnt, chnl)              ":" SERVERNAME " 474 " + clnt + " " + chnl + " :Cannot join because you are banned\r\n"
#define ERR_BADCHANNELKEY(clnt, chnl)               ":" SERVERNAME " 475 " + clnt + " " + chnl + " :Incorrect channel key\r\n"
#define ERR_NONICKNAMEGIVEN(clnt)                   ":" SERVERNAME " 431 " + clnt + " :No nickname provided\r\n"
#define ERR_ERRONEUSNICKNAME                        ":" SERVERNAME " 432 :Erroneous nickname\r\n"
#define ERR_NICKNAMEINUSE                           ":" SERVERNAME " 433 :Nickname is already in use\r\n"//TODO: Incorrect format
#define ERR_ALREADYREGISTERED(clnt)                 ":" SERVERNAME " 462 " + clnt + " :You are already registered\r\n"
#define ERR_PASSWDMISMATCH                          ":" SERVERNAME " 464 :Incorrect password\r\n"//TODO: Incorrect format
#define ERR_INVITEONLYCHAN(clnt, chnl)              ":" SERVERNAME " 473 " + clnt + " " + chnl + " :Invite only channel\r\n"
#define ERR_CHANNELISFULL(clnt, chnl)               ":" SERVERNAME " 471 " + clnt + " " + chnl + " :Channel is full\r\n"

#define ERR_NOTEXTTOSEND(clnt, cmd)					":" SERVERNAME " 461 " + clnt + " " + cmd + " :No text to send\r\n" //TODO: PROBABLY INCORRECT FORMAT
#define ERR_CANNOTSENDTOCHAN(clnt, chnl)			":" SERVERNAME " 404 " + clnt + " " + chnl + " :Cannot send to channel\r\n" //TODO: PROBABLY INCORRECT FORMAT
#define RPL_NOTOPIC(clnt, chnl)						":" SERVERNAME " 331 " + clnt + " " + chnl + " :No topic is set\r\n" //TODO: PROBABLY INCORRECT FORMAT
#define RPL_TOPIC(clnt, chnl, topic)				":" SERVERNAME " 332 " + clnt + " " + chnl + " :" + topic + "\r\n" //TODO: PROBABLY INCORRECT FORMAT
#define ERR_USERONCHANNEl(tnick, chnl)				":" SERVERNAME " 443 " + tnick + " " + chnl + " :is already on channel\r\n" //TODO: PROBABLY INCORRECT FORMAT
#define RPL_INVITING(clnt, tnick, chnl)			":" SERVERNAME " 341 " + clnt + " " + tnick + " " + chnl + " :invite\r\n" //TODO: PROBABLY INCORRECT FORMAT

char    validModeString( char mode );

template <typename T>
std::string to_string(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

// #define ERR_NEEDMOREPARAMS		reply("461", "Not enough parameters")
// #define RPL_WELCOME				reply("001", "Welcome")
// #define RPL_JOIN				reply("", "has joined a channel")
// #define ERR_BANNEDFROMCHAN		reply("474", "cannot join because they are banned")
// #define ERR_BADCHANNELKEY		reply("475", "provided an incorrect channel key")
// #define ERR_NONICKNAMEGIVEN		reply("431", "No nickname provided")
// #define ERR_ERRONEUSNICKNAME	reply("432", "ERR_ERRONEUSNICKNAME")
// #define ERR_NICKNAMEINUSE		reply("433", "Nickname already in use")
// #define ERR_ALREADYREGISTERED	reply("462", "User already registered")
// #define ERR_PASSWDMISMATCH		reply("464", "Incorrect password")
// #define ERR_INVITEONLYCHAN		reply("473", "invit only")
// #define ERR_CHANNELISFULL		reply("471", " full channel")
