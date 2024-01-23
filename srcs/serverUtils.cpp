/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:04:43 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/23 17:10:17 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "channel.hpp"

void	server::fillSockAddr(void)
{
	memset(&_serverAddrs, 0, sizeof(_serverAddrs));
	_serverAddrs.sin_family = AF_INET;
	_serverAddrs.sin_addr.s_addr = INADDR_ANY;
	_serverAddrs.sin_port = htons(_port);
}

pollfd	server::fillPollFd(int socket)
{
	pollfd	result;

	result.fd = socket;
	result.events = POLLIN;
	result.revents = 0;
	return result;
}

void	server::parseArg(int argc, char **argv)
{
	if (argc != 3)
		throw std::invalid_argument("server::InvalidArgument");
	_port = std::atol(argv[1]);
	if (_port <= 0 || _port >= 65536)
		throw std::invalid_argument("server::invalidPort");
	_passwd = std::string(argv[2]);
}

void	server::deleteChannel(std::string channelName)
{
	for(std::map<std::string, channel*>::iterator i = _channelMap.begin(); i != _channelMap.end(); i++)
	{
		if (i->first == channelName)
		{
			delete i->second;
			_channelMap.erase(i);
			break;
		}
	}
}

void	server::deleteClientSocket(int clientSocket)
{
	for (std::map<int, client*>::iterator i = _clientMap.begin(); i != _clientMap.end(); i++)
	{
		if (i->first == clientSocket)
		{
			//delete i->second;
			_clientMap.erase(i);
			break ;
		}
	}
	for (std::vector<pollfd>::iterator i = _pollFds.begin(); i != _pollFds.end(); i++)
	{
		if (i->fd == clientSocket)
		{
			_pollFds.erase(i);
			break ;
		}
	}
}

void		server::assosiateChannel(std::string channelName, int clientSocket)
{
	if (_channelMap.find(channelName) == _channelMap.end())
		_channelMap[channelName] = new channel(channelName, clientSocket);
}

void	server::assosiateClientSocket(int clientSocket)
{
	if (_clientMap.find(clientSocket) == _clientMap.end())
		_clientMap[clientSocket] = new client(clientSocket, this);
}
