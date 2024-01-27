/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:03:00 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/27 18:56:45 by cpapot           ###   ########.fr       */
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

void	channel::disconnectClient(int clientSocket, bool sendPart)
{
	for (std::map<int, client*>::iterator i = _clientMap.begin(); i != _clientMap.end(); i++)
	{
		if (i->first == clientSocket)
		{
			if (sendPart)
				sendToAll(RPL_PART(i->second->getNickname(), i->second->getUsername(), _channelName));
			_clientMap.erase(i);
			break ;
		}
	}
}

bool	channel::isInInviteList(std::string ClientNick)
{
	for (size_t i = 0; i != _inviteList.size(); i++)
	{
		if (_inviteList[i] == ClientNick)
			return true;
	}
	return false;
}

void	channel::addToInviteList(std::string ClientNick)
{
	bool	info = false;

	for (size_t i = 0; i != _inviteList.size(); i++)
	{
		if (_inviteList[i] == ClientNick)
			info = true;
	}
	if (info == false)
		_inviteList.push_back(ClientNick);
}

void	channel::removeFromInviteList(std::string ClientNick)
{
	size_t y = 0;
	for (std::vector<std::string>::iterator i = _inviteList.begin(); i != _inviteList.end(); i++, y++)
	{
		if (_inviteList[y] == ClientNick)
		{
			_inviteList.erase(i);
			break;
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
	{
		if (isInInviteList(ClientPtr->getNickname()))
			removeFromInviteList(ClientPtr->getNickname());
		else
			return INVITE_ONLY;
	}
	_clientMap[ClientPtr->getSocket()] = ClientPtr;
	return CHANNEL_JOINNED;
}

void	channel::makeOperator(int clientSocket)
{
	_operatorList.push_back(clientSocket);
}

bool	channel::isOnChannel(int socket)
{
	for (std::map<int, client*>::iterator i = _clientMap.begin(); i != _clientMap.end(); i++)
	{
		if (i->first == socket)
			return true;
	}
	return false;
}

bool	channel::isOnChannelStr(std::string ClientNick)
{
	for (std::map<int, client*>::iterator i = _clientMap.begin(); i != _clientMap.end(); i++)
	{
		if (i->second->getNickname() == ClientNick)
			return true;
	}
	return false;
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

void	channel::setIsInviteOnly(bool value)
{
	_isInviteOnly = value;
}

void	channel::setIsTopicOperator(bool value)
{
	_isTopicOperator = value;
}

void	channel::setIsLocked(bool value, std::string pass)
{
	_isLocked = value;
	_passwd = pass;
}

void	channel::setIsUserLimit(bool value, unsigned int maxUser)
{
	_isUserLimit = value;
	_maxUser = maxUser;
}

channel::channel(std::string name, int clientSocket)
{
	_channelName = name;
	_isInviteOnly = false;
	_isLocked = false;
	_isTopicOperator = false;
	_isUserLimit = false;
	if (DEBUG)
		printShit("#d new channel %s", name.c_str());
	_operatorList.push_back(clientSocket);
}

channel::~channel()
{
}
