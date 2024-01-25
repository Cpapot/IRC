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


bool	IsChannel(std::string str);

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
	message = ":" + _nickname + " PRIVMSG " + splitLine[1] + " :";
	for (size_t i = 2; i != splitLine.size(); i++)
		message += splitLine[i] + SPACE;
	message += END;
	_serverPtr->getChannel(splitLine[1])->sendToAllExept(message, _clientSocket);
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
		if (i == 2 && splitLine[i].find("DCC") == 1)
		{
			sendFile(message, splitLine, i);
			break;
		}
		reply += splitLine[y] + SPACE;
	}
	reply += END;
	_serverPtr->getClient(splitLine[1])->sendToClient(RPL_PVTMSG(_nickname, _username, splitLine[i], reply));
	return true;
}

bool	client::sendFile(std::string message, std::vector<std::string> splitLine, int i)
{
	std::cout << "sendFile" << std::endl;
	for (size_t y = i; y != splitLine.size(); y++)
	{
		message += splitLine[y] + SPACE;
	}
	message += END;
	sendToClient(message);
	if (DEBUG)
		printShit("#c Trying to send a file");
	return true;
}
