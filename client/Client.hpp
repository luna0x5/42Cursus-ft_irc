#ifndef CLIENT_HPP
#define CLIENT_HPP

#include<string>
#include<map>
#include <vector>

class Client {
    private:
        std::string ip; // by inet_ntoa
        int port;  // by ntohs
        std::string Buffer;
        std::vector<std::string> cmds; //to store all cmds ends with /r/n
        
    public:
    std::string& getBuffer(void);
    std::vector<std::string>& getCmds(void);
    void AddBuffer(const char *buf);
    void extract_cmds(void);

};

#endif