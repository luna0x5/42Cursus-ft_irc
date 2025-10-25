/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   botClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuury <yuury@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:17:55 by yuury             #+#    #+#             */
/*   Updated: 2025/10/25 21:39:15 by yuury            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Server.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>

class botClient
{
    private:
        std::string _nick;
        std::string _username;
        
        std::string _pass;
        std::string _serverIp;
        
        int         _port;
        int         _socketFd;

        std::string _buffer;

    public:
    
        botClient(const char* pass, const char* nick,
                  const char* username, const char* serverip, int port);
        botClient(const botClient& other);
        botClient& operator=(const botClient& other);
        ~botClient();
        
        void    establishConnection( void );
        void    authenticate( void );
        
        void    startBot();
        
        
    private:

        // void    send();10ms
        const std::string&    recieve();
        std::string _trim(const std::string& s);
        
};