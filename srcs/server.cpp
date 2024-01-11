/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:42:46 by cpapot            #+#    #+#             */
/*   Updated: 2024/01/11 18:43:10 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

server const	&server::operator=(const server &src)
{
	_serverAddrs = src._serverAddrs;
	_socket = src._socket;
	_passwd = src._passwd;
	_port = src._port;
	return (*this);
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

int		server::acceptClient()
{
	int clientSocket;

	if (!_status)
		throw std::invalid_argument("server::ServerNotLauched");

	std::cout << "Waiting for client" << std::endl;
	clientSocket = accept(_socket, (struct sockaddr*)&_clientAddrs, &_clientSocketLen);
	if (clientSocket == -1)
	{
		std::cout << "client can't connect" << std::endl;
		return -1;
	}
	std::cout << "Connexion accepted" << std::endl;
	return clientSocket;
}

void	server::parseArg(int argc, char **argv)
{
	if (argc <= 1)
		throw std::invalid_argument("server::PortNotSpecified");
	if (argc > 3)
		throw std::invalid_argument("server::ToMuchArg");
	_port = std::atoi(argv[1]);
	if (_port <= 0 && _port >= 10000)
		throw std::invalid_argument("server::invalidPort");
	if (argc == 2)
		_passwd = std::string("");
	else
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

server::server(int argc, char **argv)
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
	close(_socket);
}
