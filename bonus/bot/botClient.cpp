/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   botClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:28:04 by yuury             #+#    #+#             */
/*   Updated: 2025/10/27 22:39:39 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "botClient.hpp"
#include "../Inc/bot.hpp"
#include <fcntl.h>

botClient::botClient(const std::string& nick)
{
    this->_nick = nick;
    registerCommands();

    this->_socketFd = socket(AF_INET, SOCK_STREAM, 0);

    if (this->_socketFd == -1)
        throw std::runtime_error("Error: Failed to create bot socket!");
    
    int flags = fcntl(this->_socketFd, F_GETFL, 0);
    if (flags == -1) { 
        close(this->_socketFd); 
        throw std::runtime_error("Error: Failed to get socket flags!");
    }
    if (fcntl(this->_socketFd, F_SETFL, flags | O_NONBLOCK) == -1) {
        close(this->_socketFd);
        throw std::runtime_error("Error: Failed to set socket to non-blocking!");
    }
}

botClient::~botClient()
{
    close(this->_socketFd);
}


void
botClient::establishConnection()
{
    this->address.sin_family = AF_INET;
    this->address.sin_port = htons(this->_serverPort);

    WLOG( "Connecting to " << this->_serverAddress << ":" << this->_serverPort );

    if (this->_serverAddress == LOCALHOST)
    {
        this->address.sin_addr.s_addr = inet_addr(this->_serverAddress.c_str());
    }
    else{
          struct hostent *host_info = gethostbyname(this->_serverAddress.c_str());

        if (host_info == NULL)
        {
            std::string error_msg = "Error: DNS lookup failed for '" + this->_serverAddress + "': ";
            switch (h_errno) {
                case HOST_NOT_FOUND: error_msg += "Host not found."; break;
                case NO_ADDRESS:     error_msg += "No IP address found for host."; break;
                case NO_RECOVERY:    error_msg += "Non-recoverable name server error."; break;
                case TRY_AGAIN:      error_msg += "Temporary error in name server. Try again."; break;
                default:             error_msg += "Unknown DNS error."; break;
            }
            throw std::runtime_error(error_msg);
        }

        this->address.sin_addr.s_addr = *(in_addr_t *)host_info->h_addr_list[0];
        LOG("DNS resolved " << this->_serverAddress << " to " << inet_ntoa(this->address.sin_addr));
    }

    if (connect(this->_socketFd, (struct sockaddr *)&this->address, sizeof(this->address)) == -1)
    {
        if (errno == EINPROGRESS) {
            WLOG("Connection in progress (non-blocking)...");
        }
        else {
            throw std::runtime_error("Error: Failed to connect to server ");
        }
    }
    else {
        LOG("Connection established immediately.");
    }
    sleep(1);
}

void
botClient::authenticate()
{
    std::string auth[3] = {
        "PASS " + this->_password + "\r\n",
        "NICK " + this->_nick + "\r\n",
        "USER " + this->_nick + " 0 * :" + this->_nick + "\r\n"
    };
    int i = 0;
    if (this->_password.empty())
        i++;

    for (; i < 3; i++)
    {        
        sendMessage(this->_socketFd, auth[i]);
        
        usleep(1000);

        std::stringstream s(receiveMessage(this->_socketFd));
        if (s.str().empty())
            continue;
     
        std::string server;
        int         err;
        if (s >> server >> err && ERROR(err))
            throw std::runtime_error("Error: " + s.str());
    }

    LOG("===================Authentication successful================");
  
}


void
botClient::privmsg(const std::string &target, const std::string &message)
{
    std::string fullmsg = "PRIVMSG " + target + " :" + message + "\r\n";
    sendMessage(this->_socketFd, fullmsg);
    LOG("sent=> " << fullmsg);
}

msg botClient::_parseMsg(const std::string &line)
{
    std::string target;
    std::string cmd;
    if (line.find("PRIVMSG") != std::string::npos)
    {
        size_t  begining = line.find(':');
        size_t  end      = line.find('!');
        if (begining != std::string::npos && end != std::string::npos)
            target = line.substr(begining + 1, end - begining - 1);
        begining = line.find(" :");
        cmd = line.substr(begining + 2);
    }
    msg res;
    res.content = cmd;
    res.target = target;
    return res;
}


void
botClient::startBot()
{
    while (true)
    {
        std::string line = receiveMessage(this->_socketFd);
        std::replace(line.begin(), line.end(), '\r', '\n');

        std::vector<std::string> lines = split(line, '\n');

        for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); it++)
        {
            std::string trimmed = trim(*it);
            if (trimmed.empty())
                continue;
            LOG("Received <=" << trimmed);
            if (trimmed.find("PING") != std::string::npos)  
            {
                sendMessage(this->_socketFd, "PONG");
                LOG("Sent => PONG");
            } 
            else if (trimmed.find("PRIVMSG") != std::string::npos)
            {
                msg target = _parseMsg((*it));
                // LOG("Parsed message: target=" << target.target << ", content=" << target.content);
                std::map<std::string, commands>::iterator it = commandList.find(target.content);

                if (it != commandList.end()) 
                {
                    commands func = it->second;
                    (this->*func)(target.target);
                } 
                else
                    this->privmsg(target.target, "Unknown command: " + target.content);
            }
        }
    }
}



void
botClient::prompt( void )
{
    LOG("Bot prompt> ");
    std::cout << "enter server address: ";
    std::cin >> this->_serverAddress;
    if (this->_serverAddress == "localhost")
        this->_serverAddress = LOCALHOST;
    std::cout << "enter server port: ";
    std::string port;
    std::cin >> port;
    int portint = std::atoi(port.c_str());
    // std::cout << portint;
    if (portint >= 1024 && portint < 65535)
        this->_serverPort = portint;
    else 
        throw std::runtime_error("Error: Invalid port number : " + port);
    std::cout << "enter bot password: ";
    std::cin >> this->_password;
    std::cout << "enter bot nickname: ";
    std::cin >> this->_nick;
    if (this->_nick.empty())
        this->_nick = DEFAULT_NICK;
}