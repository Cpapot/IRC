/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:42:46 by cpapot            #+#    #+#             */
/*   Updated: 2024/02/12 18:49:02 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "client.hpp"
#include "serverLogs.hpp"
#include "channel.hpp"


					/*Constructors*/

server::server(/* args */)
{
	_status = true;
	_port = 6667;
	_passwd = "1234";
	this->fillSockAddr();
	this->launch();
}

server::server(int argc, char **argv): _serverName("IRC++")
{
	_status = false;
	this->parseArg(argc, argv);
	this->fillSockAddr();
	this->launch();
	_logs = new serverLogs(_port);
	_status = true;
}

server::~server()
{
	
		printShit("#i Closing %s", _serverName.c_str());
	for (std::map<int, client*>::iterator i = _clientMap.begin(); i != _clientMap.end(); i++)
		delete i->second;
	for (std::map<std::string, channel*>::iterator i = _channelMap.begin(); i != _channelMap.end(); i++)
		delete i->second;
	close(_socket);
	delete _logs;
}


					/*Getters*/


std::string		server::getPasswd(void)
{
	return (_passwd);
}

bool	server::getStatus(void)
{
	return (_status);
}

int	server::getSocket(void)
{
	return (_socket);
}

struct sockaddr_in	server::getAddrs(void)
{
	return (_serverAddrs);
}

channel	*server::getChannel(std::string channelName)
{
	for(std::map<std::string, channel*>::iterator i = _channelMap.begin(); i != _channelMap.end(); i++)
	{
		if (i->second->getChannelName() == channelName)
			return i->second;
	}
	return NULL;
}

client	*server::getClient(std::string nickname)
{
	for (std::map<int, client*>::iterator i = _clientMap.begin(); i != _clientMap.end(); i++)
	{
		if (i->second->getNickname() == nickname)
			return i->second;
	}
	return NULL;
}

serverLogs			*server::getLogs(void)
{
	return _logs;
}


					/*Server functions*/


void	server::sendToAllNetwork(std::string message)
{
	for (std::map<int, client*>::iterator i = _clientMap.begin(); i != _clientMap.end(); i++)
		i->second->sendToClient(message);
}

int		server::acceptClient()
{
	int clientSocket;

	if (!_status)
		throw std::invalid_argument("server::ServerNotLauched");
	clientSocket = accept(_socket, (struct sockaddr*)&_clientAddrs, &_clientSocketLen);
	if (clientSocket == -1)
	{
		std::cout << "log(-1) failed: " << std::strerror(errno) << '\n';
		std::cout << "client can't connect" << std::endl;
		return -1;
	}
	printShit("#d Connexion accepted");
	return clientSocket;
}

void		server::launch(void)
{
	//crée un socket (comme un fd)
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == -1)
		return throw std::invalid_argument("server::FailedToOpenSocket");
	//affecte le socket a un nom
	if(bind(_socket, (struct sockaddr*)&_serverAddrs, (socklen_t)sizeof(_serverAddrs)) == -1)
		return throw std::invalid_argument("server::FailedToBindSocket(PortMayBeBusy)");
	if (listen(_socket, MAXCLIENT) == -1)
		return throw std::invalid_argument("server::FailedToListenOnSocket");
	printShit("#i Server %s launched on port %d with password %s", _serverName.c_str(), _port, _passwd.c_str());
}


int		server::WaitForClient(void)
{
	if (_pollFds.size() == 0)
		_pollFds.push_back(fillPollFd(_socket));
	while (true)
	{
		if (poll(_pollFds.data(), _pollFds.size(), -1) == -1)
			throw std::invalid_argument("server::PollError");
		for (size_t i = 0; i < _pollFds.size(); i++)
		{
			if (_pollFds[i].revents && POLLIN)
			{
				if (_pollFds[i].fd == _socket)
				{
					// NOUVEL USER
					int	newClientSocket = acceptClient();
					_pollFds.push_back(fillPollFd(newClientSocket));
					assosiateClientSocket(newClientSocket);
					if (!_clientMap[newClientSocket]->listenToClient())
						deleteClientSocket(newClientSocket);
				}
				else
				{
					// ANCIEN USER
					if (!_clientMap[_pollFds[i].fd]->listenToClient())
						deleteClientSocket(_pollFds[i].fd);
				}
			}
		}
	}
}