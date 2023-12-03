/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:43:48 by cpapot            #+#    #+#             */
/*   Updated: 2023/12/03 07:18:10 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <cstring>
# include <iostream>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <cstdlib>
# include <cerrno>

# define MAXCLIENT 64

class server
{
protected:
	int					_socket;
	struct sockaddr_in	_serverAddrs;
private:
	std::string			_passwd;
	uint16_t			_port;
public:
	//server(std::string _passwd, std::string _port);
	server();
	~server();

	void	fillSockAddr();
	int		launch(void);
};

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
	_port = 6667;
	_passwd = "1234";
	this->fillSockAddr();
	if (this->launch())
		std::cout << "server lauched" << std::endl;
}

server::~server()
{
}

#endif
