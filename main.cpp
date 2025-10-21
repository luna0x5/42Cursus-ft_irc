#include "Server.hpp"

int main(int ac, char **av) {
    if (ac != 3) {
        std::cerr <<" <port> <password>" << std::endl;
        return 1;
    }
//     struct rlimit rl;
// getrlimit(RLIMIT_NOFILE, &rl);
// std::cout << "Soft limit: " << rl.rlim_cur << ", Hard limit: " << rl.rlim_max << std::endl;

//     std::cout << "EAGAIN: " << EAGAIN << std::endl;
//     std::cout << "EWOULDBLOCK: " << EWOULDBLOCK << std::endl;

    int port;
    std::stringstream ss(av[1]);
    ss >> port;
    if (port < 1 || port > 65535) {
        std::cerr << "Invalid port number." << std::endl;
        return 1;
    }

    

    Server test(port, av[2]);
    // test.parse_cmd(":nick!user@host JOIN #channel :Hello everyone!");
    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, Server::Handler);
    signal(SIGQUIT, Server::Handler);
    test.start();

}
