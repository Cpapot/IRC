/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:03:00 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/21 21:33:32 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"
#include "IRCMessage.hpp"

std::string	channel::getChannelName(void)
{
	return (_channelName);
}

void	channel::sendToAll(std::string message)
{
	for (std::map<int, client*>::iterator i = _clientMap.begin(); i != _clientMap.end(); i++)
			i->second->sendToClient(message);
}

void	channel::sendToAllExept(std::string message, int senderSocket)
{
	for (std::map<int, client*>::iterator i = _clientMap.begin(); i != _clientMap.end(); i++)
	{
		if (i->first != senderSocket)
			i->second->sendToClient(message);
	}
}

void	channel::disconnectClient(int clientSocket)
{
	for (std::map<int, client*>::iterator i = _clientMap.begin(); i != _clientMap.end(); i++)
	{
		if (i->first == clientSocket)
		{
			sendToAll(RPL_PART(i->second->getNickname(), i->second->getUsername(), _channelName));
			_clientMap.erase(i);
			break ;
		}
	}
}

enum {CHANNEL_JOINNED = 0, ALREADY_LOGGED, NO_SUCH_SPACE, BADPASS, INVITE_ONLY};
int		channel::newClient(client *ClientPtr, std::vector<std::string> splitLine)
{
	if (_clientMap.find(ClientPtr->getSocket()) != _clientMap.end())
		return ALREADY_LOGGED;
	if (_isUserLimit && _clientMap.size() >= _maxUser)
		return NO_SUCH_SPACE;
	if (_isLocked && splitLine[2] != _passwd)
		return BADPASS;
	if (_isInviteOnly)
		return INVITE_ONLY;
	_clientMap[ClientPtr->getSocket()] = ClientPtr;
	std::cout << ClientPtr->getNickname() << " joinded " << _channelName << std::endl;
	return CHANNEL_JOINNED;
}

void	channel::makeOperator(int clientSocket)
{
	_operatorList.push_back(clientSocket);
}
void	channel::deleteOperator(int clientSocket)
{
	size_t y = 0;
	for (std::vector<int>::iterator i = _operatorList.begin(); i != _operatorList.end(); i++, y++)
	{
		if (_operatorList[y] == clientSocket)
		{
			_operatorList.erase(i);
			break;
		}
	}
}


bool	channel::isOperator(int clientSocket)
{
	for (size_t i = 0; i != _operatorList.size(); i++)
	{
		if (_operatorList[i] == clientSocket)
			return true;
	}
	return false;
}

channel::channel(std::string name, int clientSocket)
{
	_channelName = name;
	_isInviteOnly = false;
	_isLocked = false;
	_isTopicOperator = false;
	_isUserLimit = false;
	std::cout << "new channel: " << name << std::endl;
	_operatorList.push_back(clientSocket);
}

channel::~channel()
{
}
