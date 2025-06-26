/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:10:58 by hmoukit           #+#    #+#             */
/*   Updated: 2025/06/26 15:50:36 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

void client::setUser(std::string username)
{
    userName = username;
}

std::string client::getUser()
{
    return (userName);
}

void client::setNick(std::string nickname)
{
    nickName = nickname;
}

std::string client::getNick()
{
    return (nickName);
}

void client::setIsAuth(bool isauth)
{
    isAuth = isauth;
}

bool client::getIsAuth()
{
    return (isAuth);
}
