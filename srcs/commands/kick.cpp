/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:47:43 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/25 17:41:12 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "channel.hpp"
#include "IRCMessage.hpp"

//KICK #Finnish John :Speaking English
bool	client::kick(std::vector<std::string> splitLine)
{
	std::string kickMsg("");

	if (splitLine.size() < 3)
	{
		sendToClient(ERR_NEEDMOREPARAMS(_nickname, _username));
		return false;
	}
	if (_serverPtr->getChannel(splitLine[1]) == NULL)
	{
		sendToClient(ERR_NOSUCHCHANNEL(_nickname, _username, splitLine[1]));
		return false;
	}
	if (!_serverPtr->getChannel(splitLine[1])->isOnChannel(_clientSocket))
	{
		sendToClient(ERR_NOTONCHANNEL(_nickname, _username, splitLine[1]));
		return false;
	}
	if (!_serverPtr->getChannel(splitLine[1])->isOperator(_clientSocket))
	{
		sendToClient(ERR_CHANOPRIVSNEEDED(_nickname, _username, splitLine[1]));
		return false;
	}
	if (!_serverPtr->getChannel(splitLine[1])->isOnChannelStr(splitLine[2]))
	{
		sendToClient(ERR_USERNOTINCHANNEL(_nickname, _username, splitLine[1]));
		return false;
	}
	for (size_t i = 3; i != splitLine.size(); i++)
	{
		kickMsg += splitLine[i];
		if (splitLine.size() != i + 1)
			kickMsg += SPACE;
	}
	kickMsg.erase(0, 1);
	_serverPtr->getChannel(splitLine[1])->sendToAll(RPL_KICK(_nickname, _username, splitLine[1], splitLine[2], kickMsg));
	_serverPtr->getChannel(splitLine[1])->disconnectClient(_serverPtr->getClient(splitLine[2])->getSocket(), false);
	return true;
}
