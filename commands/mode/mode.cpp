/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 01:55:22 by ychagri           #+#    #+#             */
/*   Updated: 2025/08/26 00:52:50 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void
Server::MODE( void )
{
    if (this->_line.size() < 2)
        return (this->sendErr(ERR_NEEDMOREPARAMS, "MODE"));
    
    // else if (this->)

}