/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:36:25 by ychagri           #+#    #+#             */
/*   Updated: 2025/09/04 10:46:40 by ychagri          ###   ########.fr       */
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

char    validModeString( const std::string &mode )
{
    std::string validModes("-+itkol");

    for (size_t i = 0; i < mode.length(); i++)
        if (validModes.find(mode[i]) == std::string::npos)
            return mode[i];

    return (-1);
}