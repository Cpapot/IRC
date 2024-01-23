/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:00:30 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/23 16:55:44 by cpapot           ###   ########.fr       */
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
	if (_serverPtr->getClient(splitLine[1]) != NULL)
	{
		/*std::string oldNick = splitLine[1];
		while (_serverPtr->getClient(splitLine[1]) != NULL)
			splitLine[1] = splitLine[1] + std::string("_");
		_nickname = splitLine[1];
		std::cout << _nickname << std::endl;*/
		sendToClient(ERR_NICKNAMEINUSE(splitLine[1]));
		_badNick = true;
		return false;
	}
	if (_nickname == "")
	{
		_nickname = splitLine[1];
		_serverPtr->sendToAllNetwork(RPL_NICK(_nickname, _username, splitLine[1]));
		if (_badNick == true && _userAnswerSent == false)
		{
			sendToClient(RPL_USER(_nickname, _username, WELCOME_MSG));
			_userAnswerSent = true;
			_badNick = false;
		}
	}
	else
	{
		_serverPtr->sendToAllNetwork(RPL_NICK(_nickname, _username, splitLine[1]));
		_nickname = splitLine[1];
	}
	return true;
}
