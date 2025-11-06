/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   botClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:17:55 by yuury             #+#    #+#             */
/*   Updated: 2025/11/06 13:45:58 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
// #include "Server.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <vector>
#include <map>
#include <unistd.h>
#include <netdb.h>
#include <sstream>
#include <string>
#include <ctime>
#include <cerrno>
#include <algorithm>
#include <cstdlib>

typedef struct msg
{
    std::string target;
    std::string content;
} msg;

class botClient
{
    private:

        botClient(const botClient& other);
        botClient& operator=(const botClient& other);
    
        int         _socketFd;
        std::string _serverAddress;
        int         _serverPort;
        sockaddr_in  address;
        std::string _nick;
        std::string _password;
          
        void    registerCommands(void);
        void    greeting(const std::string &target);
        void    ping(const std::string &target);
        void    stime(const std::string &target);
        
        msg     _parseMsg(const std::string &line);
        void    privmsg(const std::string &target, const std::string &message); 

            
        typedef void (botClient::*commands)(const std::string &);
        std::map<std::string, commands> commandList;
        
    public:

        botClient(const std::string& nick);
        ~botClient();
        
        void    prompt( void );

        void    establishConnection(); 
        void    authenticate();
        void    startBot();        
};