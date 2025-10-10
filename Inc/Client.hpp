#ifndef CLIENT_HPP
#define CLIENT_HPP

#include<string>
#include<map>
#include <vector>

class Client {
    private:
        std::string ip;
        std::string Buffer;
        std::vector<std::string> cmds; //to store all cmds ends with /r/n
        
        
        bool isPassed; // defaul 0
        bool isNick;
        bool isUser;
        bool registered; //default 0


        // int reg_done;
        // bool Op;
        std::string nickname;
        std::string username;
        std::string realname;
        int         _fd;
        
    public:
        Client();
        ~Client();
        std::string& getBuffer(void);
        std::vector<std::string>& getCmds(void);


        void set_is_user(bool u);
        bool get_is_user(void);
        bool get_is_nick(void);
        void set_is_nick(bool n);
        bool getisPassed(void);
        void setisPassed(bool s);


        bool getregistered(void);
        void setregistered(bool r);
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