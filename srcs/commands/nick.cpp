/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:00:30 by cpapot            #+#    #+#             */
/*   Updated: 2024/02/12 16:45:12 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "server.hpp"
#include "channel.hpp"
#include "print.hpp"

bool	testString(std::string str, std::string invalidChar);

bool	client::nick(std::vector<std::string> splitLine)
{
	if (!testString(splitLine[1], " &#:\r\n\t\v"))
	{
		sendToClient(std::string(ERR_ERRONEUSNICKNAME(_nickname, _username)));
		return false;
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
		printShit("#d set his nickname to %s", _username.c_str(), _nickname.c_str());
		_nickname = splitLine[1];
	}
	return true;
}
