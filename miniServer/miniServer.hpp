/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:35:18 by hmoukit           #+#    #+#             */
/*   Updated: 2025/06/26 15:52:20 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISERVER_HPP
# define MINISERVER_HPP

# include "../auth/auth.hpp"

class miniServer {
private:
    int socketFd;
    int port;

public:
    miniServer(int port);         // Constructor
    ~miniServer();                /// Destructor
    void start();                 // Calls serverSocket + run loop
private:
    int serverSocket();           // Handles socket setup
    void handleClient(int clientFd); // to handle client connections
};


#endif