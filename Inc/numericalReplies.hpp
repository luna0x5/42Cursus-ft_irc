/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericalReplies.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 01:17:18 by ychagri           #+#    #+#             */
/*   Updated: 2025/08/26 00:49:31 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>


typedef struct s_replies
{
    std::string code;
    std::string msg;
} reply;


#define ERR_NEEDMOREPARAMS	reply{"461", "Not enough parameters"}//Not enough parameters provided for command

void sendServerRpl(int const client_fd, std::string client_buffer); //This function takes a client file descriptor and a formatted message buffer, then sends the message to the appropriate client.