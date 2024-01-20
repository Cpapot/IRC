/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:00:30 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/20 18:03:20 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "server.hpp"
#include "channel.hpp"
#include "print.hpp"

bool	client::nick(std::vector<std::string> splitLine)
{
	std::string invalidChar = " &#:\r\n\t\v";

	for (size_t i = 0; i != splitLine[1].size(); i++)
	{
		for (size_t y = 0; y != invalidChar.size(); y++)
		{
			if (splitLine[1][i] == invalidChar[y])
			{
				sendToClient(std::string(ERR_ERRONEUSNICKNAME(_nickname, _username)));
				return false;
			}
		}
	}
	_nickname = splitLine[1];
	return true;
}
