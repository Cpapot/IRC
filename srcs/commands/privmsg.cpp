/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:57:07 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/29 12:21:19 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "IRCMessage.hpp"
#include "server.hpp"
#include "channel.hpp"
#include "print.hpp"


bool	IsChannel(std::string str);
bool	isDcc(std::string line);

bool	client::privmsg(std::vector<std::string> splitLine)
{
	std::string message;
	if (splitLine.size() <= 2)
	{
		sendToClient(std::string(ERR_NEEDMOREPARAMS(_nickname, _username)));
		return false;
	}
	if (!IsChannel(splitLine[1]))
	{	
		if (!_serverPtr->getClient(splitLine[1]))
		{
			sendToClient(ERR_NOSUCHNICK(_nickname, _username, splitLine[1]));
			return false;
		}
		else
			return (privateMessage(message, splitLine, 1));
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
	splitLine[2].erase(0, 1);
	for (size_t i = 2; i != splitLine.size(); i++)
		message += splitLine[i] + SPACE;
	message += END;
	_serverPtr->getChannel(splitLine[1])->sendToAllExept(RPL_CHANMSG(_nickname, splitLine[1], message), _clientSocket);
	if (DEBUG)
		printShit("#c PRIVMSG : %s : %s", _username.c_str(), message.c_str());
	return true;
}

bool	client::privateMessage(std::string message, std::vector<std::string> splitLine, int i)
{
	std::string reply;
	i++;
	for (size_t y = i; y != splitLine.size(); y++)
	{
		if (y == 2 && isDcc(splitLine[y]))
		{
			sendFile(message, splitLine, i);
			return true;
		}
		reply += splitLine[y] + SPACE;
	}
	reply += END;
	_serverPtr->getClient(splitLine[1])->sendToClient(RPL_PVTMSG(_nickname, _username, splitLine[i], reply));
	return true;
}

bool	isDcc(std::string line)
{
	int isOkay = 0;

	if (line[2] == 'D')
		isOkay = 1;
	if (line[3] == 'C' && isOkay == 1)
		isOkay = 1;
	if (line[4] == 'C' && isOkay == 1)
		return (true);
	return (false);
}

std::string		getSize(std::string message)
{
	std::string	size;
	for (int i = 0; i != (int)message.size() - 1; i++)
	{
		size += message[i];
	}
	return (size);
}

bool	client::sendFile(std::string message, std::vector<std::string> splitLine, int i)
{
	for (size_t y = i; y != splitLine.size(); y++)
	{
		message += splitLine[y];
		if (y != splitLine.size() - 1)
			message += SPACE;
	}
	_serverPtr->getClient(splitLine[1])->sendToClient(RPL_DCC(_nickname, _username, message, splitLine[1]));
	if (DEBUG)
		printShit("#c Trying to send a file");
	return true;
}
