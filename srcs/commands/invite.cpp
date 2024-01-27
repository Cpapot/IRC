/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:35:49 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/27 18:36:34 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "channel.hpp"
#include "IRCMessage.hpp"

bool	client::invite(std::vector<std::string> splitLine)
{
	if (splitLine.size() < 3)
	{
		sendToClient(ERR_NEEDMOREPARAMS(_nickname, _username));
		return false;
	}
	if (_serverPtr->getClient(splitLine[1]) == NULL)
	{
		sendToClient(ERR_NOSUCHNICK(_nickname, _username, splitLine[1]));
		return false;
	}
	if (_serverPtr->getChannel(splitLine[2]) == NULL)
	{
		sendToClient(ERR_NOSUCHCHANNEL(_nickname, _username, splitLine[2]));
		return false;
	}
	if (!_serverPtr->getChannel(splitLine[2])->isOnChannel(_clientSocket))
	{
		sendToClient(ERR_NOTONCHANNEL(_nickname, _username, (splitLine[2])));
		return false;
	}
	if (_serverPtr->getChannel(splitLine[2])->isOnChannelStr(splitLine[1]))
	{
		sendToClient(ERR_USERONCHANNEL(_nickname, _username, splitLine[1], splitLine[2]));
		return false;
	}
	sendToClient(RPL_INVITING(_nickname, _username, splitLine[1], splitLine[2]));
	_serverPtr->getClient(splitLine[1])->sendToClient(RPL_INVITE(_nickname, _username, splitLine[1], splitLine[2]));
	_serverPtr->getChannel(splitLine[2])->addToInviteList(splitLine[1]);
	return true;
}
