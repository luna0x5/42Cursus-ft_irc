/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuury <yuury@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:36:25 by ychagri           #+#    #+#             */
/*   Updated: 2025/10/16 00:55:23 by yuury            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::vector<std::string>    ftSplit(const std::string& str, const char del)
{
    std::vector<std::string>    tokens;
    std::string                 token;
    std::stringstream           ss(str);

    while (std::getline(ss, token, del))
    {
        if (!token.empty())
            tokens.push_back(token);
    }

    return tokens;
}

char    validModeString( char mode )
{
    std::string validModes("-+itkol");

    if (validModes.find(mode) != std::string::npos)
        return mode;

    return (-1);
}
