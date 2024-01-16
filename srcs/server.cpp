/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:42:46 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/16 21:07:54 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "client.hpp"

server const	&server::operator=(const server &src)
{
	_serverAddrs = src._serverAddrs;
	_socket = src._socket;
	_passwd = src._passwd;
	_port = src._port;
	return (*this);
}

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

pollfd	server::fillPollFd(int socket)
{
	pollfd	result;

	result.fd = socket;
	result.events = POLLIN;
	result.revents = 0;
	return result;
}

void	server::deleteClientSocket(int clientSocket)
{
	for (std::map<int, client*>::iterator i = _clientMap.begin(); i != _clientMap.end(); i++)
	{
		if (i->first == clientSocket)
		{
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

void	server::assosiateClientSocket(int clientSocket)
{
	if (_clientMap.find(clientSocket) == _clientMap.end())
		_clientMap[clientSocket] = new client(clientSocket, this);
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
	std::cout << "Connexion accepted" << std::endl;
	return clientSocket;
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

void	server::parseArg(int argc, char **argv)
{
	if (argc != 3)
		throw std::invalid_argument("server::InvalidArgument");
	_port = std::atoi(argv[1]);
	if (_port <= 0 && _port >= 10000)
		throw std::invalid_argument("server::invalidPort");
	_passwd = std::string(argv[2]);
}

int		server::launch(void)
{
	//crée un socket (comme un fd)
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == -1)
	{
		std::cout << "Failed to open socket." << std::endl;
		return 0;
	}
	//affecte le socket a un nom
	if(bind(_socket, (struct sockaddr*)&_serverAddrs, (socklen_t)sizeof(_serverAddrs)) == -1)
	{
		std::cout << "Failed to bind socket." << std::endl;
		std::cout << "log(-1) failed: " << std::strerror(errno) << '\n';
		return 0;
	}
	if (listen(_socket, MAXCLIENT) == -1)
	{
		std::cout << "Failed to listen on socket." << std::endl;
		return 0;
	}
	return 1;
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
					_clientMap[newClientSocket]->listenToClient();
				}
				else
				{
					// ANCIEN USER
					_clientMap[_pollFds[i].fd]->listenToClient();
				}
			}
		}
	}
}

void	server::fillSockAddr(void)
{
	memset(&_serverAddrs, 0, sizeof(_serverAddrs));
	_serverAddrs.sin_family = AF_INET;
	_serverAddrs.sin_addr.s_addr = INADDR_ANY;
	_serverAddrs.sin_port = htons(_port);
}

server::server(/* args */)
{
	_status = true;
	_port = 6667;
	_passwd = "1234";
	this->fillSockAddr();
	if (this->launch())
		std::cout << "server lauched" << std::endl;
	else
		_status = false;
}

server::server(int argc, char **argv): _serverName("IRC++")
{
	_status = true;
	try
	{
		this->parseArg(argc, argv);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		_status = false;
		return ;
	}
	this->fillSockAddr();
	if (this->launch())
		std::cout << "server lauched" << std::endl;
	else
		_status = false;

}

server::~server()
{
	for (std::map<int, client*>::iterator i = _clientMap.begin(); i != _clientMap.end(); i++)
		delete i->second;
	close(_socket);
}
