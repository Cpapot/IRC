/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:57:07 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/23 17:19:24 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "server.hpp"
#include "channel.hpp"
#include "print.hpp"

bool	client::privmsg(std::vector<std::string> splitLine)
{
	std::string message;
	if (splitLine.size() <= 2)
	{
		sendToClient(std::string(ERR_NEEDMOREPARAMS(_nickname, _username)));
		return false;
	}
	if (!_serverPtr->getChannel(splitLine[1]))
	{
		sendToClient(std::string(ERR_NOSUCHCHANNEL(_nickname, _username, splitLine[1])));
		return false;
	}
	if (!_serverPtr->getChannel(splitLine[1])->isOnChannel(_clientSocket))
	{
		sendToClient(ERR_NOTONCHANNEL(_nickname, _username, splitLine[1]));
		return false;
	}
	message = ":" + _nickname + " PRIVMSG " + splitLine[1] + " :";
	splitLine[2].erase(0, 1);
	for (size_t i = 2; i != splitLine.size(); i++)
		message += splitLine[i] + SPACE;
	message += END;
	_serverPtr->getChannel(splitLine[1])->sendToAllExept(message, _clientSocket);
	new Print(message, MAGENTA, 3);
	return true;
}
