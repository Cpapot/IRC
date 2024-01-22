/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:03:00 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/20 16:35:03 by cpapot           ###   ########.fr       */
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

//0 = ok 1 = alreadylog 2 = no space
int		channel::newClient(client *ClientPtr)
{
	if (_clientMap.find(ClientPtr->getSocket()) != _clientMap.end())
		return 1;
	_clientMap[ClientPtr->getSocket()] = ClientPtr;
	sendToAll(RPL_JOIN(ClientPtr->getNickname(), _channelName));
	std::cout << ClientPtr->getNickname() << " joined " << _channelName << std::endl;
	return 0;
}

channel::channel(std::string name)
{
	_channelName = name;
	std::cout << "new channel: " << name << std::endl;
}

channel::~channel()
{
}
