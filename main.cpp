/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:35:13 by hmoukit           #+#    #+#             */
/*   Updated: 2025/09/14 12:54:27 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "Server.hpp"

int main(int ac, char **av) {
    if (ac != 3) {
        std::cerr <<" <port> <password>" << std::endl;
        return 1;
    }
    int port;
    std::stringstream ss(av[1]);
    ss >> port;
    if (port < 1 || port > 65535) {
        std::cerr << "Invalid port number." << std::endl;
        return 1;
    }
    Server test(port, av[2]);
    // test.parse_cmd(":nick!user@host JOIN #channel :Hello everyone!");
    // signal(SIGPIPE, SIG_IGN);
    // signal(SIGINT, Server::Handler);
    // signal(SIGQUIT, Server::Handler);
    test.start();
}
