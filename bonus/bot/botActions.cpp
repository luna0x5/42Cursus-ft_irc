#include "botClient.hpp"
#include "../Inc/bot.hpp"

void
botClient::greeting(const std::string &target)
{
    this->privmsg(target, "hi theeere!!");   
}

void
botClient::ping(const std::string &target)
{
    this->privmsg(target, "pong");   
}

void
botClient::stime(const std::string &target)
{
    time_t rawtime;
    time(&rawtime);
    struct tm* timeinfo;
    timeinfo = localtime(&rawtime);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

    this->privmsg(target, "the Current server time is : " + std::string(buffer));   
}


void botClient::registerCommands() {
    // How to populate the map    
    commandList["!hello"] = &botClient::greeting;
    commandList["!time"] = &botClient::stime;
    commandList["!ping"] = &botClient::ping;
    
}