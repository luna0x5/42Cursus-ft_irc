/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuury <yuury@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:08:23 by yuury             #+#    #+#             */
/*   Updated: 2025/10/25 18:30:33 by yuury            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "botClient.hpp"

int main(int ac, char **av)
{
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
    try
    {
        // std::cerr << "llll" << std::endl;
        botClient bot(av[2], "bot", "yuury", "127.0.0.1", port);
        bot.establishConnection();
        bot.authenticate();
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}