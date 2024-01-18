/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:26:23 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/18 12:31:51 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <string>
#include "client.hpp"

class channel
{
private:
	std::string				_chanelName;

	std::map<int, client*>	_clientMap;
public:
	channel(std::string	name);
	~channel();

	int		newClient(client *ClientPtr);
	void	disconnectClient(int clientSocket);

	void	sendToAll(std::string message);
};

void	channel::sendToAll(std::string message)
{
	for (std::map<int, client*>::iterator i = _clientMap.begin(); i != _clientMap.end(); i++)
		i->second->sendToClient(message);
}

void	channel::disconnectClient(int clientSocket)
{
	for (std::map<int, client*>::iterator i = _clientMap.begin(); i != _clientMap.end(); i++)
	{
		if (i->first == clientSocket)
		{
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
	std::cout << ClientPtr->getNickname() << " joinded " << _chanelName << std::endl;
	return 0;
}

channel::channel(std::string name)
{
	_chanelName = name;
}

channel::~channel()
{
}


#endif
