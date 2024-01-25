/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:00:33 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/25 17:21:38 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "server.hpp"
#include "channel.hpp"
#include "print.hpp"

bool	client::part(std::vector<std::string> splitLine)
{
	if (splitLine.size() != 2)
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
	//_serverPtr->getChannel(splitLine[1])->sendToAll(RPL_PART(_nickname, _username, splitLine[1]));
	_serverPtr->getChannel(splitLine[1])->disconnectClient(_clientSocket, 1);
	if (DEBUG)
		printShit("#d %s left %s", _username.c_str(), splitLine[1].c_str());
	return true;
}
