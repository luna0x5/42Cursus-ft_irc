/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:10:55 by hmoukit           #+#    #+#             */
/*   Updated: 2025/06/26 15:50:52 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTH_HPP
# define AUTH_HPP

# include <iostream>
# include <sys/socket.h>
# include <fcntl.h>
# include <netinet/in.h>
# include <poll.h>
# include <stdexcept>
# include <unistd.h>
# include <errno.h>

class client {
    private:
        std::string userName;
        std::string nickName;
        bool isAuth;
    public:
        void setUser(std::string username);
        std::string getUser();
        void setNick(std::string nickname);
        std::string getNick();
        void setIsAuth(bool isauth);
        bool getIsAuth();
};

#endif