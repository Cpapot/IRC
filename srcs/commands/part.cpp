/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:00:33 by cpapot            #+#    #+#             */
/*   Updated: 2024/03/01 12:32:08 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "server.hpp"
#include "channel.hpp"
#include "print.hpp"

bool	client::part(std::vector<std::string> splitLine)
{
	if (splitLine.size() < 1)
	{
		sendToClient(ERR_NEEDMOREPARAMS(_nickname, _username));
		return false;
	}
	for (size_t i = 0; i != _loggedChannel.size(); i++)
	{
		if (_loggedChannel[i] == splitLine[1])
			break;
		if (i == _loggedChannel.size() - 1)
		{
			if (_serverPtr->getChannel(splitLine[1]) != NULL)
				sendToClient(ERR_NOTONCHANNEL(_nickname, _username, splitLine[1]));
			else
				sendToClient(ERR_NOSUCHCHANNEL(_nickname, _username, splitLine[1]));
			return false;
		}
	}
	std::string message;
	for (unsigned long i = 2; i < splitLine.size(); i++)
		message += splitLine[i] + SPACE;
	_serverPtr->getChannel(splitLine[1])->disconnectClient(_clientSocket, 1, message);
	printShit("#c %s left %s", _username.c_str(), splitLine[1].c_str());
	return true;
}
