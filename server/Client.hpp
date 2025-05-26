#ifndef CLIENT_HPP
#define CLIENT_HPP

#include<string>
#include<map>

class Client {
    private:
        std::string ip; // by inet_ntoa
        int port;  // by ntohs
        std::string Buffer;
        std::map<int, std::string> map_buffer; 
        //maybe i will replace the string in map by all client as an objet and move it to the server class
        

    public:

};

#endif