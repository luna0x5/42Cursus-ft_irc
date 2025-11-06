#include "Server.hpp"
#include "Channel.hpp"


volatile sig_atomic_t flag = 0;

Server::Server(uint port , std::string password): _port(port), _password(password)
{
    initCmds();
}

Server::~Server()
{
   cleaner();
}

int
Server::server_socket()
{
    int err;

    this->_Socket_fd = socket(AF_INET, SOCK_STREAM, 0);// setting server socket with tcp connection and ipv4 
    checkErr(this->_Socket_fd , -1, "Error: Failed to create server socket!");
    //check if the errno == EINTR
    
    err = fcntl(this->_Socket_fd, F_SETFL , O_NONBLOCK);// setting the socket to non blocking for concurrency
    checkErr(err, -1, "Error: Failed to set socket flag!");

    int opt = 1;
    err = setsockopt(this->_Socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));// Allowing multiple sockets to bind to the same address and port
    checkErr(err, -1, "Error: Failed to set socket option!");

    sockaddr_in server_addr;// ipv4 socket address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->_port);// converting port to network byte order 
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);// inaddr to listen for all connections

    err = bind(_Socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));// naming the socket
    checkErr(err, -1, "Error: Failed to bind!");
    
    err = listen(_Socket_fd, SOMAXCONN);// marking the socket as passive (tcp)
    checkErr(err, -1, "Error: Failed to listen!");
  
    // preparing listening socket to be monitored by poll for new incoming connections
    pollfd listen_fd;
    listen_fd.fd = this->_Socket_fd;
    listen_fd.events = POLLIN;
    this-> _poll_fds.push_back(listen_fd);

    return(this->_Socket_fd);
}

void
Server::running_server(int Socket_fd)
{
    while(!flag)
    // while(true)
    {
        int monitor = poll(this->_poll_fds.data(), this->_poll_fds.size(), -1);//poll to monitor multiple fds without i/o blocking
        if (monitor == -1 && errno == EINTR)
            continue;
        checkErr(monitor, -1, "Error : Failed poll");

        for (size_t i = 0; i < this->_poll_fds.size(); i++)
        {
            if (this->_poll_fds[i].revents & POLLIN)//checks if a pollin (data to read) event occured
            {
                if (this->_poll_fds[i].fd == Socket_fd)// checking if fd whith the POLLIN event is the listening socket(new connection request)
                {
                    try{
                        handle_new_connections(_Socket_fd);
                    }
                    catch(std::exception& e){ // ??????
                        std::cerr<<e.what()<<std::endl;
                    }
                }
                else
                {
                    char buffer[1024];
                    memset(buffer, 0, sizeof(buffer));
                    int bytes = recv(this->_poll_fds[i].fd, buffer, sizeof(buffer) - 1, 0);
                    if (bytes <= 0)
                    {
                        if (bytes == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
                            continue; // No data available right now, try again later
                        }
                        remove_client(this->_poll_fds[i].fd, i);
                        i--;
                        continue;
                    }
                    else
                    {
                        buffer[bytes] = '\0';
                        _client[this->_poll_fds[i].fd].AddBuffer(buffer);
                        
                        _client[this->_poll_fds[i].fd].extract_cmds();
                        handle_client_data(this->_poll_fds[i].fd);
                    }
                }
            }
        }
    }
    cleaner();
}

void Server::start(){
    int socket_fd;
    try{
        socket_fd = server_socket();
        running_server(socket_fd);
    }
    catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
}

void
Server::checkErr(const int res, const int err, const char *msg)
{
    if (res == err)
        throw std::runtime_error(msg);
    return ;
}

void Server::Handler(int){
    flag = 1;
}

void Server::remove_client(int fd, int i){
    for (ch_it it = this->_channel.begin(); it != this->_channel.end();){
        Channel &chan = it->second;
        std::string message = ":" + this->_client[fd].getPrefix() + " QUIT " + chan.GetName() + "\r\n";
        if (chan.is_Member(this->_client[fd].getnick())){
            chan.rmMember(&this->_client[fd]);
            chan.broadcastReply(message);
            if (chan.is_Op(fd)){
                chan.rmOps(&this->_client[fd]);
            }
            if (chan.getMembersCount() == 0){
                ch_it tmp = it;
                ++it;
                this->_channel.erase(tmp);
                continue;
            }
        }
        ++it;
    }
    close(fd);
    std::cout<<  " -> client : " <<fd << " is disconnected!" <<std::endl;
    _client.erase(fd);
    this->_poll_fds.erase(this->_poll_fds.begin() + i);
}
