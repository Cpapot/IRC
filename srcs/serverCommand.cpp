/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:10:50 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/16 19:26:58 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "client.hpp"
#include "IRCMessage.hpp"

bool	server::whoIs(int clientSocket, std::vector<std::string> splitline)
{
	if (splitline.size() == 1)
	{
		_clientMap[clientSocket]->sendToClient(std::string(ERR_NONICKNAMEGIVEN));
		return false;
	}
	for (std::map<int, client*>::iterator i = _clientMap.begin(); i != _clientMap.end(); i++)
	{
		if (splitline[1] == i->second->getNickname())
		{
			_clientMap[clientSocket]->sendToClient(std::string(RPL_WHOISUSER(i->second->getNickname(), i->second->getUsername(), \
				i->second->getHostname(), i->second->getRealname())));
			break;
		}
		if (i == _clientMap.end()--)
		{
			_clientMap[clientSocket]->sendToClient(std::string(ERR_NOSUCHNICK(splitline[1])));
			return false;
		}
	}
	return true;
}

bool	server::ping(int clientSocket, std::vector<std::string> splitLine)
{
	if (splitLine.size() == 1)
	{
		_clientMap[clientSocket]->sendToClient(std::string(ERR_NEEDMOREPARAMS));
		return false;
	}
	_clientMap[clientSocket]->sendToClient(std::string("PONG ") + _serverName + SPACE + splitLine[1]);
	return true;
}


