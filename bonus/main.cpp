/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:08:23 by yuury             #+#    #+#             */
/*   Updated: 2025/11/06 14:27:51 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Inc/bot.hpp"

int main()
{
    try
    {
        // PARSER METHODS 
        botClient bot(DEFAULT_NICK);
        bot.prompt();
        bot.establishConnection();
        bot.authenticate();
        bot.startBot(); 
    
    }
    catch (const std::exception &e)
    {
        ELOG(e.what());
    }
    return 0;
}