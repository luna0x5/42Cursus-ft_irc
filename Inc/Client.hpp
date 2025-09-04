#ifndef CLIENT_HPP
#define CLIENT_HPP

#include<string>
#include<map>
#include <vector>

class Client {
    private:
        std::string ip; // by inet_ntoa
        // int port;  // by ntohs
        std::string Buffer;
        // int port;  // by ntohs
        std::vector<std::string> cmds; //to store all cmds ends with /r/n
        bool registered; //default 0
        bool isPassed; // defaul 0
        int reg_done;
        // bool Op;
        std::string nickname;
        std::string username;
        std::string realname;
        int         _fd;
        
    public:
        std::string& getBuffer(void);
        std::vector<std::string>& getCmds(void);
        bool getregistered(void);
        void setregistered(bool r);
        bool getisPassed(void);
        void setisPassed(bool s);
        void AddBuffer(const char *buf);
        void extract_cmds(void);
        std::string& GetUsername(void);
        void SitUsername(std::string user);
        void setreg(void);
        int getreg(void);
        std::string getnick(void);
        void setnick(std::string nick);
        std::string getuser(void);
        void setuser(std::string user);
        void setrealname(std::string real);
        std::string getrealname(void);

        void            setFd(const int fd);
        int             getFd( void ) const;

};

#endif