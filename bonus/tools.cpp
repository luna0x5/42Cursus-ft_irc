#include "Inc/bot.hpp"
#include <sstream>
#include <cstdlib>

void sendMessage(int socketFd, const std::string& message) {
    usleep(rand() % 1000);
    std::string fullMessage = message + "\r\n";
    if (send(socketFd, fullMessage.c_str(), fullMessage.length(), 0) == -1)
        throw std::runtime_error("Error: Failed to send message!");
};

std::string receiveMessage(int socketFd) {
    char buffer[1024];
    ssize_t bytesReceived = recv(socketFd, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived == 0) 
        throw std::runtime_error("Error: Connection closed by peer!");
    else if (bytesReceived == -1)
        return "";
    buffer[bytesReceived] = '\0';
    return std::string(buffer);
}

std::string trim(const std::string& s) {
    size_t start = 0;
    size_t end = s.size();

    while (start < end && (std::isspace(s[start]) || s[start] == '\t' || s[start] == '\n'))
        ++start; 
    while (end > start && (std::isspace(s[end - 1]) || s[end - 1] == '\t' || s[end - 1] == '\n'))
        --end;
    return s.substr(start, end - start);
}

std::vector<std::string> split(std::string &line, char del)
{
    std::vector<std::string> result;
    std::stringstream s(line);
    std::string       item;

    while (std::getline(s, item, del))
    {
        result.push_back(item);
    }
    return result;
}