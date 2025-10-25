/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   botClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuury <yuury@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:28:04 by yuury             #+#    #+#             */
/*   Updated: 2025/10/25 21:43:52 by yuury            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "botClient.hpp"

botClient::botClient(const char* pass, const char* nick, 
                    const char* username, const char* serverip,
                    int port):_nick(nick), _username(username), _pass(pass), 
                    _serverIp(serverip), _port(port), _socketFd(-1) {}

botClient::botClient(const botClient& other)
{
    *this = other;
}

botClient&
botClient::operator=(const botClient& other)
{
    if (this != &other)
    {
        if (this->_socketFd != -1)
            close(this->_socketFd);
        this->_pass = other._pass;
        this->_nick = other._nick;
        this->_username = other._username;
        this->_serverIp = other._serverIp;
        this->_port = other._port;
        // this->_socketFd = other._socketFd; 
    }
    return *this;
}

botClient::~botClient()
{
    if (this->_socketFd != -1)
        close(this->_socketFd);
}

void
botClient::establishConnection( void )
{
    this->_socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_socketFd == -1)
        throw std::runtime_error("Error: Failed to create bot socket!");

    sockaddr_in serv_Address;
    serv_Address.sin_family = AF_INET;
    serv_Address.sin_port = htons(this->_port);
    serv_Address.sin_addr.s_addr = inet_addr(this->_serverIp.c_str());

    if(connect(this->_socketFd, (sockaddr *)&serv_Address, sizeof(serv_Address)) == -1)
        throw std::runtime_error("Error: Connection to server failed!");
}

void
botClient::authenticate( void )
{

    std::string pass = "PASS " + this->_pass + "\r\n";
    std::string nick = "NICK " + this->_nick + "\r\n";
    std::string user = "USER " + this->_username + " 0 * :bot\r\n";
    // if (send(this->_socketFd, pass.c_str(), pass.length(), 0) == -1
    //   || send(this->_socketFd, nick.c_str(), nick.length(), 0) == -1
    //   || send(this->_socketFd, user.c_str(), user.length(), 0) == -1)
    //     throw std::runtime_error("Error: authentication with server failed!");

    if (send(this->_socketFd, pass.c_str(), pass.length(), 0) == -1)
        throw std::runtime_error("Error: authentication with server failed!");
    usleep(10000);
    if (send(this->_socketFd, nick.c_str(), nick.length(), 0) == -1)
        throw std::runtime_error("Error: authentication with server failed!");
    usleep(10000);
    if (send(this->_socketFd, user.c_str(), user.length(), 0) == -1)
        throw std::runtime_error("Error: authentication with server failed!");

    
    char buf[1024];
    int n = recv(this->_socketFd, &buf, 1023, 0);
    if (n  == -1)
        throw std::runtime_error("Error: authentication with server failed!");

    buf[n] = 0;
    std::string buff(buf);
    if (buff.find("001") == std::string::npos)
        throw std::runtime_error("Error: authentication with server failed!");    
}

const std::string&
botClient::recieve()
{
    char buf[1024];
    int n = recv(this->_socketFd, &buf, sizeof(buf) - 1, 0);
    if (n  == 0)
        throw std::runtime_error("Error: server disconnected!");
    
    if (n == -1) 
    {
        if (errno == EWOULDBLOCK || errno == EAGAIN)
            return "";
        throw std::runtime_error("Error: recv failed!");
    }
    buf[n] = 0;
    this->_buffer += buf;
    size_t crlf_pos = this->_buffer.find("\r\n");
    if (crlf_pos != std::string::npos) {
        std::string line = this->_buffer.substr(0, crlf_pos);
        this->_buffer.erase(0, crlf_pos + 2);
        return line;
    }
    return "";
}

std::string
botClient::_trim(const std::string& s) {
    size_t start = 0;
    size_t end = s.size();

    while (start < end && std::isspace(s[start]))
        ++start;

    while (end > start && std::isspace(s[end - 1]))
        --end;

    return s.substr(start, end - start);
}

void
botClient::startBot()
{
    while (true)
    {
        std::string line = recieve();
        if (!line.empty())
        {
            std::string trimline = this->_trim(line);
            if (trimline == "help")
            {
                //help; 
                
            }
            else if (trimline == "whois")
            {
                
            }
            else if (trimline == "listusers")
            {
                
            }
            else if (trimline == "listcmds")
            {
                
            }
            else
            {
                //error
            }
            
        }
    }
}